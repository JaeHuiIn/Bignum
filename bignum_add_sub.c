#include "bignum_add_sub.h"
// 덧셈과 뺄셈 구현

// bigint 덧셈
void bi_add(bigint* x, bigint* y, bigint** C)
{;
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
	for (int i = 0; i < min_len; i++)    // x + y 부분 실행
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

	// x + 0 또는 y + 0 수행
	if (flag == 1) {
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
	bi_refine(*C);
}


// bigint 뺄셈
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
		(*C)->a[i] = (x->a[i]);
	}
}
void bi_sub(bigint* x, bigint* y, bigint** C)
{
	int max_len;
	if (x->wordlen > y->wordlen) {
		max_len = x->wordlen;
	}
	else if (y->wordlen > x->wordlen) {
		max_len = y->wordlen;
	}
	else {
		max_len = x->wordlen;
	}
	bi_new(C, max_len);

	if (is_zero(x) == 0)
	{
		bi_assign(C, y);
		bi_flip_sign(C);    // -Y를 리턴
	}
	else if (is_zero(y) == 0)
	{
		bi_assign(C, x);    // X를 리턴
	}

	if (x->sign == 0 && y->sign == 0)    // x, y 둘다 양수
	{
		if (Compare_ABS(x, y) == 1)  // x > y > 0
		{
			bi_subc(x, y, C);
		}
		else if (Compare_ABS(x, y) == 0) // x == y > 0
		{
			bi_set_zero(C);
		}
		else if (Compare_ABS(x, y) == -1)    // y > x > 0
		{
			bi_subc(y, x, C);
			bi_flip_sign(C);
		}
	}
	else if (x->sign != y->sign) // 둘 중 한개만 양수
	{
		if (x->sign == 0) // x > 0, y < 0
		{
			bi_add(x, y, C);    // add에서 sign을 사용하지 않는다.
		}
		else    // x < 0, y > 0
		{
			bi_add(x, y, C);
			bi_flip_sign(C);
		}
	}
	else if (x->sign == -1 && y->sign == -1)
	{
		if (Compare_ABS(x, y) == 1)      // * 안넣는게 맞나? ㅠ
		{
			bi_subc(x, y, C);
			bi_flip_sign(C);
		}
		else if (Compare_ABS(x, y) == 0)
		{
			bi_set_zero(C);
		}
		else if (Compare_ABS(x, y) == -1)
		{
			bi_subc(x, y, C);
		}
	}

}