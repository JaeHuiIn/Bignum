#include "bignum_all_header.h"

// school book division
void bi_sb_div(bigint* A, bigint* B, bigint** Q, bigint** R)
{
	if(B->sign == NEGATIVE || is_zero(B) == 0) {	// B <= 0
		printf("INVALID");
		return;
	}

	if(Compare_ABS(A, B) == -1){	// A < B
		bi_set_zero(Q);		// Q <- 0
		bi_assign(R, A);	// assign "A" to "R"
		return;
	}

	if(is_one(B) == 1) {	// B == 1
		bi_assign(Q, A);	// assign "A" to "Q" 
		bi_set_zero(R);		// R <- 0
		return;
	}

	bi_set_zero(Q);		// Q <- 0
	bi_assign(R, A);	// assign "A" to "R"

	bigint* ONE = NULL;
	bi_set_one(&ONE);	// ONE <- 0
	
	while(Compare_ABS(*R, B) >= 0) {	// R >= B
		bi_self_add(Q, ONE);	// Q <- Q + ONE

		bigint* R_temp = NULL;	
		bi_assign(&R_temp, *R);	// assign "R" to "R_temp"
		bi_subc(R_temp, B, R);	// R <- R_temp - B
		bi_delete(&R_temp);	

	}


	bi_delete(&ONE);

}

void Binary_Long_Division(bigint* A, bigint* B, bigint** Q, bigint** R)
{
	bi_set_zero(Q);		// Q <- 0
	bi_set_zero(R);		// R <- 0

	bigint* TEMP = NULL;
	bigint* R_TEMP = NULL;

	word one = 1ULL << (WORD_BITLEN - 1);
	int n = (A->wordlen) * WORD_BITLEN;
	
	while (1)
	{
		if ((A->a[(A->wordlen) - 1] & one) - one == 0)
			break;
		one = one >> 1;
		n--;
	}
	int a_j;

	for(int j = n-1; j >= 0; j--) {
		a_j = get_jth_bit(A, j);
		Left_Shift(R, 1);	// R <- 2R
		(*R)->a[0] += a_j;	// R을 1비트 왼쪽 쉬프트 하면 LSB는 항상 0이된다. 따라서 LSB에 0 또는 1인 a_j 추가. (or 연산으로 구현하는것도 가능할듯)

		if (Compare_ABS(*R, B) > 0) {	// if R >= B
			bi_set_one(&TEMP);		// TEMP = 1
			Left_Shift(&TEMP, j);	// 1 << j 	-->  2^j 구현
			bi_self_add(Q, TEMP);	// Q <- Q + 2^j

			bi_assign(&R_TEMP, *R);
			bi_subc(R_TEMP, B, R);
		}
	}


	bi_delete(&TEMP);
	bi_delete(&R_TEMP);

}

//	Long division algorithm for 2 word
void L_D_A(bigint* A, word B, bigint** Q) 
{
	bigint* R = NULL;
	bi_new(&R, 1);
	int j;
	int w = WORD_BITLEN - 1;
	bi_new(Q, 1);
	bi_new(&R, 1);
	bi_set_zero(Q);	// Q <- 0
	R->a[0] = A->a[1];	// R <- A1

	word upper = (1ULL << (WORD_BITLEN - 1));
	for (j = w; j >= 0; j--)
	{
		if (R->a[0] >= upper)
		{
			(*Q)->a[0] += 1ULL << j;                               // Q <- Q + 2^j
			R->a[0] = 2 * (R->a[0]) + ((A->a[0] & (1ULL << j)) >> j) - B;    // R <- 2R + a_j - B
		}
		else
		{
			R->a[0] = 2 * (R->a[0]) + ((A->a[0] & (1ULL << j))>>j);    // R <- 2R + a_j
			if (R->a[0] >= B)                                          // if R >= B
			{
				(*Q)->a[0] += 1ULL << j;                               // Q <- Q + 2^j
				R->a[0] = (R->a[0]) - B;                               // R <- R - B
			}
		}
	}


	bi_delete(&R);
}

void bi_divcc(bigint* A, bigint* B, bigint** Q, bigint** R)
{
    int n = A->wordlen;
    int m = B->wordlen;

	bigint* Copy_A = NULL;
	bi_new(Q, 1);
	bi_new(R, 1);
	bi_new(&Copy_A, 2);

    if(n == m)
        (*Q)->a[0] = A->a[n-1] / B->a[m-1];
	else if (n == m + 1)
	{
		if (A->a[m] == B->a[m - 1]) {
			(*Q)->a[0] = WORD_MASK;
		}
		else {
			Copy_A->a[1] = A->a[m];
			Copy_A->a[0] = A->a[m-1];
			L_D_A(Copy_A, B->a[m-1], Q);	// Q <- Copy_A / B->a[m-1]
		}
	}
	bigint* BQ = NULL;

    bi_mul(B, (*Q), &BQ);	// BQ <- B * Q
    bi_sub(A, BQ, R);		// R <- A - BQ
   
	// 근사시킨 Q_hat으로 Q를 구한다. 이를 위해 1 원소를 가지는 bignum을 생성
    while((*R)->sign == NEGATIVE) 
    {  // while R < 0 

	    (*Q)->a[0] -= 1;   // Q = Q - 1;
	   	bi_self_add(R, B);    // R <-> R + B;
   	}
  	bi_delete(&BQ);
	bi_delete(&Copy_A);
}

void bi_divc(bigint* A, bigint* B, bigint** Q, bigint** R)
{
    if (Compare_ABS(A, B) != 1) {	// A >= B
        bi_set_zero(Q);	// Q <- 0
        bi_assign(R, A);	// assign "A" to "R"
        return;
    }
    int m = B->wordlen; 
    word upper = 1ULL << (WORD_BITLEN - 1);  // 2^{w-1} 생성

    word B_m1 = B->a[m - 1];

    // compute k such that 2^k * B_{m-1} >= 2^{w-1}
    int k = 0;
    while(1) {
        if (B_m1 >= upper)
            break;
        else
        {
            k += 1;
            B_m1 = B_m1 << 1;
        }
        
    }
    bigint* A_dash = NULL;
    bigint* B_dash = NULL;
    bi_assign(&A_dash, A);	// assign "A" to "A_dash"
    bi_assign(&B_dash, B);	// assign "B" to "B_dash"
    Left_Shift(&A_dash, k);	// A_dash << k
    Left_Shift(&B_dash, k);	// B_dash << k

    bigint* Q_dash = NULL;
    bigint* R_dash = NULL;    
    bi_new(&Q_dash, 1);
    bi_new(&R_dash, 1);
    bi_divcc(A_dash, B_dash, &Q_dash, &R_dash);	// A_dash = B_dash * Q_dash + R_dash

	Right_Shift(&R_dash, k);	// R_dash << k
    bi_assign(Q, Q_dash);	// assign "Q_dash" to "Q"
    bi_assign(R, R_dash);	// assign "R_dash" to "R"

    bi_delete(&A_dash);
    bi_delete(&B_dash);
    bi_delete(&Q_dash);
    bi_delete(&R_dash);

}

void DIV(bigint* A, bigint* B, bigint** Q, bigint** R)
{
    if(B->sign == NEGATIVE) {	// B < 0
        printf("invalid division\n");
        return;
    }

    if(Compare_ABS(A, B) == -1) {	// A < B
        bi_set_zero(Q);		// Q <- 0
        bi_assign(R, A);	// assgin "A" to "R"
    }
	else if (Compare_ABS(A, B) == 0) {    // A == B
		bi_set_one(Q);		// Q <- 1
		bi_set_zero(R);		// R <- 0
	}
	else
	{
		bi_set_zero(Q);		// Q <- 0
		bi_set_zero(R);		// R <- 0

		int n = A->wordlen;
		bigint* A_i = NULL;
		bigint* Q_i = NULL;
		bigint* R_temp = NULL;
		bi_set_zero(&A_i);	// A_i <- 0
		bi_new(&Q_i, 1);		
		bi_new(Q, n);
		for (int i = n - 1; i >= 0; i--) {
			Left_Shift(R, WORD_BITLEN);		// R << WORD_BITLEN
			A_i->a[0] = A->a[i];
			bi_self_add(R, A_i);	// R <- R + A_i
			bi_assign(&R_temp, *R);	// assign "R" to "R_temp"
			bi_divc(R_temp, B, &Q_i, R);	// R_temp = B * Q_i + R
			(*Q)->a[i] = Q_i->a[0];

		}
		bi_refine(*Q);	// refine Q
		bi_refine(*R);	// refine R
		bi_delete(&A_i);
		bi_delete(&Q_i);
		bi_delete(&R_temp);
	}
}
