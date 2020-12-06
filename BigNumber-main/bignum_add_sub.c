#include "bignum_all_header.h"


void bi_add(bigint* x, bigint* y, bigint** C)
{
	if(x->sign != NEGATIVE && y->sign == NEGATIVE) {
		y->sign = NON_NEGATIVE;
		bi_sub(x, y, C);	// C <- x - y
		return;
	}
	else if(x->sign == NEGATIVE && y->sign != NEGATIVE) {
		x->sign = NON_NEGATIVE;
		bi_sub(y, x, C);	// C <- y - x
		return;
	}
	int min_len;
	int max_len;
	int flag;
	if (x->wordlen > y->wordlen) {
		min_len = y->wordlen;
		max_len = x->wordlen;
		flag = 1;
	}
	else if (y->wordlen > x->wordlen) {
		min_len = x->wordlen;
		max_len = y->wordlen;
		flag = 0;
	}
	else {
		min_len = x->wordlen;
		max_len = x->wordlen;
		flag = -1;
	}

	bi_new(C, max_len + 1);	

	word c = 0;
	word c1 = 0;
	for (int i = 0; i < min_len; i++)    // x + y 
	{
		c1 = 0;
		(*C)->a[i] = (x->a[i] + y->a[i]);

		if ((*C)->a[i] < x->a[i])
			c1 = 1;

		(*C)->a[i] = ((*C)->a[i] + c);

		if ((*C)->a[i] < c)
			c1 += 1;
		c = c1;
	}


	if (flag == 1) {	// x + 0 or y + 0
		for (int i = min_len; i < max_len; i++)
		{
			(*C)->a[i] = (x->a[i] + c);

			if ((*C)->a[i] < c)
				c = 1;
			else
				c = 0;
		}
	}
	else if (flag == 0) {
		for (int i = min_len; i < max_len; i++)
		{
			(*C)->a[i] = (y->a[i] + c);

			if ((*C)->a[i] < c)
				c = 1;
			else
				c = 0;
		}
	}

	if (c == 1)
		(*C)->a[max_len] = 1;
	bi_refine(*C);	// refine C

	if(x->sign == NON_NEGATIVE && y->sign == NON_NEGATIVE)
		(*C)->sign = NON_NEGATIVE;
	else if(x->sign == NEGATIVE && y->sign == NEGATIVE)
		(*C)->sign = NEGATIVE;
}

void bi_self_add(bigint** x, bigint* y)
{
	bigint* Copy_x = NULL;
	bi_assign(&Copy_x, *x);	// assign "x" to "Copy_x"
	bi_add(Copy_x, y, x);	// x <- Copy_x + y
	bi_delete(&Copy_x);		
}


void bi_subc(bigint* x, bigint* y, bigint** C)  // x >= y > 0 에서 x - y
{
	word b = 0;

	for (int i = 0; i < y->wordlen; i++)
	{
		(*C)->a[i] = (x->a[i] - b);
		if (x->a[i] < b)
			b = 1;
		else
			b = 0;

		if ((*C)->a[i] < y->a[i])
			b += 1;

		(*C)->a[i] = (*C)->a[i] - y->a[i];
	}
	for (int i = y->wordlen; i < x->wordlen; i++)
	{
		(*C)->a[i] = (x->a[i] - b);
		if (x->a[i] < b)
			b = 1;
		else
			b = 0;
	}
}


void bi_sub(bigint* x, bigint* y, bigint** C)
{
	bigint* Copy_C = NULL;
	bigint* Copy_x = NULL;
	bigint* Copy_y = NULL;

	bi_assign(&Copy_x, x);		// assign "x" to "Copy_x"  
	bi_assign(&Copy_y, y);		// assign "y" to "Copy_y"


	int max_len;
	if (Copy_x->wordlen > Copy_y->wordlen) {
		max_len = Copy_x->wordlen;
	}
	else if (Copy_y->wordlen > Copy_x->wordlen) {
		max_len = Copy_y->wordlen;
	}
	else {
		max_len = Copy_x->wordlen;
	}

	bi_new(&Copy_C, max_len);

	if (is_zero(Copy_x) == 0)	// if Copy_x is 0
	{
		bi_assign(&Copy_C, y);	// assign "y" to "Copy_C"
		bi_flip_sign(&Copy_C);  // Copy_C <- -Copy_C
	}
	else if (is_zero(Copy_y) == 0)	// if Copy_y is 0
	{
		bi_assign(&Copy_C, x);    // assign "x" to "Copy_C"
	}
	else
	{
		if (Copy_x->sign == NON_NEGATIVE && Copy_y->sign == NON_NEGATIVE)    // x > 0 and y > 0
		{
			if (Compare_ABS(Copy_x, Copy_y) == 1)  	// x > y > 0
			{
				bi_subc(Copy_x, Copy_y, &Copy_C);	// Copy_C <- Copy_x - Copy_y
			}
			else if (Compare_ABS(Copy_x, Copy_y) == 0) // x == y > 0
			{
				bi_set_zero(&Copy_C);				// Copy_C <- 0
			}
			else if (Compare_ABS(Copy_x, Copy_y) == -1)    // y > x > 0
			{
				bi_subc(Copy_y, Copy_x, &Copy_C);	// Copy_C <- Copy_y - Copy_x
				bi_flip_sign(&Copy_C);	// Copy_C <- - Copy_C
			}
		}
		else if (Copy_x->sign != Copy_y->sign) // 둘 중 한개만 양수
		{
			if (Copy_x->sign == NON_NEGATIVE) // x > 0, y < 0
			{
				bi_flip_sign(&Copy_y);	// Copy_y <- - Copy_y
				bi_add(Copy_x, Copy_y, &Copy_C);	// Copy_C <- Copy_x + Copy_y
			}
			else    // x < 0, y > 0
			{
				bi_flip_sign(&Copy_x);	// Copy_x <- - Copy_x
				bi_add(Copy_x, Copy_y, &Copy_C);	// Copy_y <- Copy_x + Copy_y
				bi_flip_sign(&Copy_C);	// Copy_C <- - Copy_C
			}
		}
		else if (Copy_x->sign == NEGATIVE && Copy_y->sign == NEGATIVE)	// x < 0, y < 0
		{
			if (Compare_ABS(Copy_x, Copy_y) == 1)      // 0 > x > y
			{
				bi_subc(Copy_x, Copy_y, &Copy_C);		// Copy_C <- Copy_x - Copy_y
				bi_flip_sign(&Copy_C);	// Copy_C <- - Copy_C
			}	
			else if (Compare_ABS(Copy_x, Copy_y) == 0)	// 0 > x == y
			{
				bi_set_zero(&Copy_C);	// Copy_C <- 0

			}
			else if (Compare_ABS(Copy_x, Copy_y) == -1)	// 0 > y > x
			{
				bi_subc(Copy_y, Copy_x, &Copy_C);	// Copy_C <- Copy_y - Copy_x
			}
		}
	}
	bi_refine(Copy_C);		// refine Copy_C
	bi_assign(C, Copy_C);	// assign "Copy_C" to "C"

	bi_delete(&Copy_C);
	bi_delete(&Copy_x);
	bi_delete(&Copy_y);

}


void bi_self_sub(bigint** x, bigint* y)	// x <- x - y
{
	bigint* Copy_x = NULL;
	bi_assign(&Copy_x, *x);	// assign "x" to "Copy_x"
	bi_sub(Copy_x, y, x);	// x <- Copy_x - y
	bi_delete(&Copy_x);		
}