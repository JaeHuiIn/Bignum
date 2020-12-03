#include "bignum_all_header.h"

void ModExp_LTR(bigint** x, bigint* n, bigint* N)    // x^n mod N
{
	bigint* t = NULL;
	bigint* x_temp = NULL;
	bigint* t_temp = NULL;
	bigint* Q_temp = NULL;
	bigint* R_temp = NULL;
	bi_assign(&x_temp, *x);
	bi_set_one(&t); // t <- 1
	word one = 1ULL << (WORD_BITLEN - 1);
	int j = n->wordlen * WORD_BITLEN;
	while (1)
	{
		if ((n->a[(n->wordlen) - 1] & one) - one == 0)
			break;
		one = one >> 1;
		j--;
	}
	// x를 저장하는 임시변수

	for (int i = j-1; i >= 0; i--) {
		bi_squaring(t, &t_temp);  // t_temp = t^2
		DIV(t_temp, N, &Q_temp, &R_temp);  // t_temp mod N (t^2 mod N)
		bi_assign(&t_temp, R_temp);
		if (get_jth_bit(n, i) == 1) {
			bi_mul(t_temp, x_temp, &t);  // t = t_temp * x 
			DIV(t, N, &Q_temp, &R_temp);       // t mod N ( t^2 * x mod N)
			bi_assign(&t, R_temp);
		}
		else
		{
			DIV(t_temp, N, &Q_temp, &R_temp);       // t mod N ( t^2 * x mod N)
			bi_assign(&t, R_temp);
		}
	}
	bi_assign(x, t);
	bi_delete(&t);
	bi_delete(&x_temp);
	bi_delete(&t_temp);
	bi_delete(&Q_temp);
	bi_delete(&R_temp);
}


void ModExp_RTL(bigint** x, bigint* n, bigint* N)
{
	bigint* t0 = NULL;
	bigint* t1 = NULL;
	bigint* Q_temp = NULL;
	bigint* R_temp = NULL;
	bigint* t0_temp = NULL;
	bigint* t1_temp = NULL;
	bigint* n_temp = NULL;
	bi_set_one(&t0);        // t0 <- 1
	bi_assign(&t1, *x);     // t1 <- x
	bi_assign(&n_temp, n);

	while (is_zero(n_temp) != 0) {
		int n_i = get_jth_bit(n_temp, 0); // n의 lsb
		Right_Shift(&n_temp, 1); 

		if (n_i == 1) {
			bi_assign(&t0_temp, t0);
			bi_mul(t0_temp, t1, &t0);
			DIV(t0, N, &Q_temp, &R_temp);  // t mod N (t^2 mod N)
			bi_assign(&t0, R_temp);
		}
		bi_squaring(t1, &t1_temp);
		bi_assign(&t1, t1_temp);
		DIV(t1, N, &Q_temp, &R_temp);  // t mod N (t^2 mod N)
		bi_assign(&t1, R_temp);

	}

	bi_assign(x, t0);
	bi_delete(&t0_temp);
	bi_delete(&t0);
	bi_delete(&t1);
	bi_delete(&t1_temp);
	bi_delete(&Q_temp);
	bi_delete(&R_temp);
	bi_delete(&n_temp);
}

void ModExp_Montgomery(bigint** x, bigint* n, bigint* N)
{
	bigint* t0 = NULL;
	bigint* t1 = NULL;
	bigint* Q_temp = NULL;
	bigint* R_temp = NULL;
	bigint* t1_temp = NULL;
	bigint* t0_temp = NULL;	
	bi_set_one(&t0);    // t0 <- 1
	bi_assign(&t1, *x); // t1 <- x

	word one = 1ULL << (WORD_BITLEN - 1);
	int j = n->wordlen * WORD_BITLEN;
	int k;
	while (1)
	{
		if ((n->a[(n->wordlen) - 1] & one) - one == 0)
			break;
		one = one >> 1;
		j--;
	}

	// j 는 n의 비트열 길이를 의미한다. j - 1 은 bit[]에서 MSB가 위치한 곳의 인덱스가 된다.  

	for (int i = j - 1; i >= 0; i--) {
		if (get_jth_bit(n, i) == 0) {
			// t1 <- t0 * t1
			bi_assign(&t1_temp, t1);
			bi_mul(t0, t1_temp, &t1);
			DIV(t1, N, &Q_temp, &R_temp);  // t mod N (t^2 mod N)
			bi_assign(&t1, R_temp);

			// t0 <- t0^2
			bi_assign(&t0_temp, t0);
			bi_squaring(t0_temp, &t0);
			DIV(t0, N, &Q_temp, &R_temp);  // t mod N (t^2 mod N)
			bi_assign(&t0, R_temp);
		}
		else {
			// t0 <- t0 * t1
			bi_assign(&t0_temp, t0);
			bi_mul(t1, t0_temp, &t0);
			DIV(t0, N, &Q_temp, &R_temp);  // t mod N (t^2 mod N)
			bi_assign(&t0, R_temp);

			// t1 <- t1^2
			bi_assign(&t1_temp, t1);
			bi_squaring(t1_temp, &t1);
			DIV(t1, N, &Q_temp, &R_temp);  // t mod N (t^2 mod N)
			bi_assign(&t1, R_temp);
		}
	}

	bi_assign(x, t0);
	bi_delete(&t1_temp);
	bi_delete(&t0_temp);
	bi_delete(&t0);
	bi_delete(&t1);
	bi_delete(&Q_temp);
	bi_delete(&R_temp);
}
