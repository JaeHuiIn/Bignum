#include "bignum_basic.h"

void array_init(word* a, int wordlen)
{
	for (int i = 0; i < wordlen; i++)
	{
		a[i] = 0x00;
	}
}

/* 2.1 Create BigInt, Delete BigInt, Zeroize BigInt */
void bi_delete(bigint** x)
{
	if (*x == NULL)
		return;

#ifdef ZERORIZE
	array_init((*x)->a, (*x)->wordlen);
#endif

	free((*x)->a);
	free(*x);
	*x = NULL;
}

void bi_new(bigint** x, int wordlen)
{
	if (*x != NULL)
		bi_delete(x);

	*x = (bigint*)malloc(sizeof(bigint));
	if (*x == NULL)
		return;
	else
	{
		(*x)->sign = NON_NEGATIVE;
		(*x)->wordlen = wordlen;
		(*x)->a = (word*)calloc(wordlen, sizeof(word));
	}
}

/* 2.2 Set BigInt, Show BigInt */
void bi_set_by_array(bigint** x, int sign, word* a, int wordlen)   // bigint x <- sign and array a
{
	(*x)->sign = sign;

	for (int i = 0; i < wordlen; i++)
	{
		(*x)->a[i] = a[i];
	}
}

/*
// developed by CJH
// 에러 많이남.
void bi_set_by_string(bigint** x, int sign, char* a, word base)   // bigint x <- base string
{
	(*x)->sign;

	int len = strlen(a);

	if(base == 2){
		int k = 0;
		for(int i = (*x)->wordlen - 1; i >= 0; i--){    // x.a[3], x.a[2], x.a[1], x.a[0] 순서대로 바이트를 집어넣는다.
			while(1) {
				(*x)->a[i] = ((*x)->a[i] << 1) | atoi(a[k]);   // 해당 x.a[i] 를 한비트 왼쪽 이동하고, 0번 인덱스 자리에 문자열의 0 또는 1을 OR연산한다.
				k += 1;
				if((len - k) % WORD_BITLEN == 0)    // len - k가 WORD_BITLEN의 배수이면 다음 x.a[i] 에 숫자를 저장해야 한다.
					break;                          // 즉, 한개의 x.a[i]에는 WORD_BITLEN 만큼 0과 1이 들어가게 된다.
			}

		}

	}
	else if(base == 10){
		// NEED TO IMPLEMENT!!
	}
	else if(base == 16){
		int k = 0;
		for(int i = (*x)->wordlen - 1; i >= 0; i--){
			while(1) {
				(*x)->a[i] = ((*x)->a[i] << 4) | atoi(a[k]);
			}
			k += 1;
			if((len - k) % WORD_BITLEN == 0)
				break;
		}

	}


}
*/

// Show big int
void bi_show(bigint* x, word base)
{
	if (x->sign == NEGATIVE) printf("-");

	if (base == 2)
	{
		for (int i = x->wordlen - 1; i >= 0; i--)
		{
			for (int j = WORD_BITLEN - 1; j >= 0; j--)
			{
				int temp = ((x->a[i]) >> j) & 0x01;
				printf("%d", temp);
			}
			printf("\t");

		}

	}
	else if (base == 10)
	{
		// NEED TO IMPLEMENT!!
	}
	else if (base == 16)
	{
		if (WORD_BITLEN == 8)
		{
			for (int i = x->wordlen - 1; i >= 0; i--)
				printf("%02x", x->a[i]);
		}
		else if (WORD_BITLEN == 32)
		{
			for (int i = x->wordlen - 1; i >= 0; i--)
				printf("%08x", x->a[i]);
		}
		else if (WORD_BITLEN == 64)
		{
			for (int i = x->wordlen - 1; i >= 0; i--)
				printf("%16x", x->a[i]);
		}
	}

}

/* 2.3 Refine BigInt (Remove Last Zero Words) */
void bi_refine(bigint* x)
{
	if (x == NULL)
		return;

	int new_wordlen = x->wordlen;
	while (new_wordlen > 1)  //  at least one word needed
	{
		if (x->a[new_wordlen - 1] != 0)
			break;
		new_wordlen--;
	}
	if (x->wordlen != new_wordlen)
	{
		x->wordlen = new_wordlen;
		x->a = (word*)realloc(x->a, sizeof(word) * new_wordlen);
	}
	else if ((x->wordlen == 1) && (x->a[0] == 0x0))
		x->sign = NON_NEGATIVE;

}

/* 2.4 Assign BigInt */
void array_copy(word y[], word x[], int wordlen)    // 수정 필요
{
	for (int i = 0; i < wordlen; i++)
	{
		y[i] = x[i];
	}
}

void bi_assign(bigint** y, bigint* x)
{
	if (*y != NULL)
		bi_delete(y);
	bi_new(y, x->wordlen);
	(*y)->sign = x->sign;
	array_copy((*y)->a, x->a, x->wordlen);
}

/* 2.5 Generate Random BigInt */
void array_rand(word* dst, int wordlen)
{
	unsigned char* p = (unsigned char*)dst;

	int cnt = wordlen * sizeof(word);

	while (cnt > 0)
	{
		*p = rand() & 0xff;
		p++;
		cnt--;
	}

}

void bi_gen_rand(bigint** x, int sign, int wordlen)
{
	bi_new(x, wordlen);
	(*x)->sign = sign;
	array_rand((*x)->a, wordlen);

	bi_refine(*x);
}


/* 2.6 Get Word Lengh / Bit Length / j-th Bit of BigInt */
int get_wordlen(bigint* x)
{
	return x->wordlen;
}

int get_bitlen(bigint* x)
{
	int bitlen = (x->wordlen - 1) * WORD_BITLEN;
	int b;
	for (int i = WORD_BITLEN - 1; i >= 0; i--)
	{
		b = (x->a[x->wordlen - 1] >> i) & 0x01;
		if (b != 0)
		{
			return bitlen + i + 1;
		}
	}
	return bitlen;
}

int get_jth_bit(bigint* x, int j)
{
	int Q = j / WORD_BITLEN;
	int R = j % WORD_BITLEN;

	if (R == 0)
	{
		return (x->a[Q]) & 0x01;
	}
	else
	{
		return ((x->a[Q]) >> R) & 0x01;
	}
}


/* 2.7 Get Sign and Flip Sign of BigInt */
int bi_get_sign(bigint* x)
{
	return x->sign;
}

void bi_flip_sign(bigint** x)
{
	if ((*x)->sign == NEGATIVE)
		(*x)->sign = NON_NEGATIVE;
	else
		(*x)->sign = NEGATIVE;
}


/* 2.8 Set One, Set Zero, Is Zero, Is One */
void bi_set_one(bigint** x)
{
	bi_new(x, 1);
	(*x)->sign = NON_NEGATIVE;
	(*x)->a[0] = 0x1;
}

void bi_set_zero(bigint** x)
{
	bi_new(x, 1);
	(*x)->sign = NON_NEGATIVE;
	(*x)->a[0] = 0x0;
}

int is_zero(bigint* x)  // 0이면 0을, 0이 아니면 1을 반환한다.
{
	for (int i = 0; i < x->wordlen; i++)    // 모든 x.a[i] 이 0인지 확인한다. 만약 0이 아니면 1 반환.
	{
		if (x->a[i] != 0)
			return 1;
	}

	return 0;
}

int is_one(bigint* x)  // 1이면 1, 1이 아니면 0을 반환한다.
{
	for (int i = 0; i < x->wordlen; i++)    // a[0]을 제외한 모든 x.a[i] 이 0인지 확인한다. 만약 0이 아니면 flag = 0로 초기화.
	{
		if (i == 0)
		{
			if (x->a[0] != 1)
				return 0;
		}
		else
		{
			if (x->a[i] != 0)
				return 0;
		}
	}

	return 1;
}

/* 2.9 Compare ABS, Compare AB*/
int Compare_ABS(bigint* A, bigint* B) // 음이 아닌 정수 A, B의 대수 비교. A > B : 1 리턴, A = B : 0 리턴, A < B : -1 리턴 
{
	int n = A->wordlen;
	int m = B->wordlen;

	if (n > m)
		return 1;
	else if (n < m)
		return -1;

	for (int j = n - 1; j >= 0; j--)
	{
		if (A->a[j] > B->a[j])
			return 1;
		else if (A->a[j] < B->a[j])
			return -1;
	}

	return 0;
}

int Compare_AB(bigint** A, bigint** B)
{
	int sign_a = (*A)->sign;
	int sign_b = (*B)->sign;
	if (sign_a == 0 && sign_b == 1)
		return 1;

	if (sign_a == 1 && sign_b == 0)
		return -1;


	int ret = Compare_ABS(*A, *B);
	if (sign_a == 0)
		return ret;
	else
		return ret * (-1);
}

/* 2.10 Left / Right Shift */
void Left_Shift(bigint** x, int r)
{
	bigint* shifted_bi = NULL; //left_shifted된 수를 저장할 공간

	int Q = r / WORD_BITLEN;  // 얼마나 앞에 더 공간이 필요한가
	int R = r % WORD_BITLEN;

	bi_new(&shifted_bi, (*x)->wordlen + Q + 1);
	array_init(shifted_bi->a, (*x)->wordlen + Q + 1); // 일단 0으로 다 채우기
	shifted_bi->sign = (*x)->sign;

	if (R == 0) // r이 WORD_BITLEN의 배수일 땐 그대로 옮겨지고 뒤에 0이 붙음
	{
		for (int i = (*x)->wordlen; i > 0; i--)
		{
			shifted_bi->a[i + Q - 1] = (*x)->a[i - 1];
		}
	}
	else
	{
		shifted_bi->a[shifted_bi->wordlen - 1] = (*x)->a[(*x)->wordlen - 1] >> (WORD_BITLEN - R);
		for (int i = (*x)->wordlen; i > 1; i--)
		{
			shifted_bi->a[i + Q - 1] = (((*x)->a[i - 1]) << R) | (((*x)->a[i - 2]) >> (WORD_BITLEN - R));
		}
		shifted_bi->a[Q] = (((*x)->a[0]) << R);
	}

	bi_refine(shifted_bi);
	bi_assign(x, shifted_bi);
	bi_delete(&shifted_bi);

}


void Right_Shift(bigint** x, int r)
{
	bigint* shifted_bi = NULL;  // 크기가 wordlen + Q + 1 인 bigint 구조체 생성

	if (r >= WORD_BITLEN * (*x)->wordlen)       // r >= w * n : 모든 bigint = 0
	{
		bi_new(&shifted_bi, 1);
		bi_set_zero(&shifted_bi);
	}
	else
	{
		int Q = r / WORD_BITLEN;                // r = w * Q + R  (0 <= R < w)
		int R = r % WORD_BITLEN;
		int size = (*x)->wordlen - Q;
		bi_new(&shifted_bi, (*x)->wordlen);
		shifted_bi->sign = (*x)->sign;

		if (R == 0)     // r이 정확히 w의 배수일 때
		{
			for (int i = 0; i < size; i++)
			{
				shifted_bi->a[i] = (*x)->a[i + Q];
			}
		}
		else
		{
			for (int i = 0; i < size - 1; i++)
			{
				shifted_bi->a[i] = (((*x)->a[i + Q]) >> R) | (((*x)->a[i + Q + 1]) << (WORD_BITLEN - R));
			}
			shifted_bi->a[size - 1] = (((*x)->a[(*x)->wordlen - 1]) >> R);
		}
		bi_refine(shifted_bi);
	}

	bi_assign(x, shifted_bi);
	bi_delete(&shifted_bi);
}

/* 2.11 Reduction */
void Reduction(bigint** A, int r)
{
	if (r < WORD_BITLEN * (*A)->wordlen)
	{
		int Q = r / WORD_BITLEN;
		int R = r % WORD_BITLEN;

		if (R == 0)
		{
			for (int i = Q; i < (*A)->wordlen; i++)
			{
				(*A)->a[i] = 0;      // Q번 워드부터 wordlen-1번 워드까지 모두 0으로 초기화. 마지막에 refine 해주기.
			}
		}
		else
		{
			for (int i = Q + 1; i < (*A)->wordlen; i++)
			{
				(*A)->a[i] = 0;      // 위와 동일하게 Q+1번 워드부터 끝까지 모두 0으로 초기화.
			}
			// 이제 a[Q] XOR (2^r - 1) 을 구현해야함.

			word a = 0x01;
			a = a << R;        // 2^R 구현
			(*A)->a[Q] = (*A)->a[Q] & (a - 1);
		}

		bi_refine(*A);
	}
}


