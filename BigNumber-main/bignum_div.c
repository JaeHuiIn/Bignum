#include "bignum_div.h"
void L_D_A(bigint* A, word B, bigint** Q)   // 함수의 자료형으로 word 사용 가능?{
{
	bigint* R = NULL;
	bi_new(&R, 1);
	int j;
	int w = WORD_BITLEN - 1;
	bi_new(Q, 1);
	bi_new(&R, 1);
	bi_set_zero(Q);
	R->a[0] = A->a[1];
	word upper = (1 << (WORD_BITLEN - 1));
	for (j = w; j >= 0; j--)
	{
		if (R->a[0] >= upper)
		{
			(*Q)->a[0] += 1 << j;
			R->a[0] = 2 * (R->a[0]) + (A->a[0] & (1 << j)) - B;
		}
		else
		{
			R->a[0] = 2 * (R->a[0]) + ((A->a[0] & (1 << j))>>j);
			if (R->a[0] >= B)
			{
				(*Q)->a[0] += 1 << j;
				R->a[0] = (R->a[0]) - B;
			}
		}
	}
}

void bi_divcc(bigint* A, bigint* B, bigint** Q, bigint** R) // 0 <= R < B, Q \in 0 ~ W 인 Q, R를 어떻게 반환할지 잘 생각해보기
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
			L_D_A(Copy_A, B->a[m-1], Q);
		}
	}

	bigint* BQ = NULL;
    // R = A - BQ를 위한 구조체 생성
    bi_mul(B, (*Q), &BQ);
    bi_sub(A, BQ, R);
    // Q_hat 계산 완료

    // 근사시킨 Q_hat으로 Q를 구한다. 이를 위해 1 원소를 가지는 bignum을 생성
   while((*R)->sign == NEGATIVE) 
   {  // while R < 0 
	   (*Q)->a[0] -= 1;   // Q = Q - 1;
	   bi_self_add(R, B);    // R = R + B;
   }
    bi_delete(&BQ);
	bi_delete(&Copy_A);
}

void bi_divc(bigint* A, bigint* B, bigint** Q, bigint** R)
{
    if (Compare_ABS(A, B) != 1) {
        bi_set_zero(Q);
        bi_assign(R, A);
        return;
    }

    int m = B->wordlen; // bigint B의 워드길이는 m이다
    int upper = (1 << (WORD_BITLEN - 1));  // 2^{w-1} 생성

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
    bi_assign(&A_dash, A);
    bi_assign(&B_dash, B);
    Left_Shift(&A_dash, k);
    Left_Shift(&B_dash, k);    

    bigint* Q_dash = NULL;
    bigint* R_dash = NULL;    
    bi_new(&Q_dash, 1);
    bi_new(&R_dash, 1);
    bi_divcc(A_dash, B_dash, &Q_dash, &R_dash);

	Right_Shift(&R_dash, k);
    bi_assign(Q, Q_dash);
    bi_assign(R, R_dash);

    bi_delete(&A_dash);
    bi_delete(&B_dash);
    bi_delete(&Q_dash);
    bi_delete(&R_dash);

}

void DIV(bigint* A, bigint* B, bigint** Q, bigint** R)
{
    if(B->sign == NEGATIVE) {
        printf("invalid division\n");
        return;
    }

    if(Compare_ABS(A, B) != 1) {
        bi_set_zero(Q);
        bi_assign(R, A);
    }
	else
	{
		bi_set_zero(Q);
		bi_set_zero(R);

		int n = A->wordlen;
		bigint* A_i = NULL;
		bigint* Q_i = NULL;
		bigint* R_temp = NULL;
		bi_set_zero(&A_i);
		bi_new(&Q_i, 1);
		bi_new(Q, n);
		for (int i = n - 1; i >= 0; i--) {
			Left_Shift(R, WORD_BITLEN);
			A_i->a[0] = A->a[i];
			bi_self_add(R, A_i);
			bi_assign(&R_temp, *R);
			bi_divc(R_temp, B, &Q_i, R);
			(*Q)->a[i] = Q_i->a[0];

		}

		bi_delete(&A_i);
		bi_delete(&Q_i);
		bi_delete(&R_temp);
	}
}
