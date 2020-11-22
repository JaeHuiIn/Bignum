#include "bignum_div.h"
/*
word L_D_A(word A1, word A0, word B)   // 함수의 자료형으로 word 사용 가능?{
{
    int upper = (1 << (WORD_BITLEN - 1));    // 2^{w-1}
    int a_j;    // A0의 j번째 비트를 저장할 변수            
    int temp = 1;
    word Q = 0;
    word R = A1;

    for(int j = WORD_BITLEN - 1; j >= 0; j--) {

        // a_j 구하기
        temp = 1  << j;
        a_j = A0 & temp;   // j 번째 인덱스의 비트와 AND 수행


        if (R >= upper) {
            Q += (1 << j);
            R = 2 * R + a_j - B;
        }
        else {
            R = 2 * R + a_j;
        }

    }

    return Q;
}
*/

void L_D_A(bigint* A, word B, bigint** Q, bigint** R)   // 함수의 자료형으로 word 사용 가능?{
{
	int j;
	int w = WORD_BITLEN - 1;
	bi_new(Q, 1);
	bi_new(R, 1);
	bi_set_zero(Q);
	(*R)->a[0] = A->a[1];
	word upper = (1 << (WORD_BITLEN - 1));
	for (j = w; j >= 0; j--)
	{
		if ((*R)->a[0] >= upper)
		{
			(*Q)->a[0] += 1 << j;
			(*R)->a[0] = 2 * ((*R)->a[0]) + (A->a[0] & (2 << j)) - B;
		}
		else
		{
			(*R)->a[0] = 2 * ((*R)->a[0]) + ((A->a[0] & (1 << j))>>j);
			if ((*R)->a[0] >= B)
			{
				(*Q)->a[0] += 1 << j;
				(*R)->a[0] = ((*R)->a[0]) - B;
			}
		}
	}
}
/*
void bi_divcc(bigint* A, bigint* B, bigint** Q, bigint** R) // 0 <= R < B, Q \in 0 ~ W 인 Q, R를 어떻게 반환할지 잘 생각해보기
{
    int n = A->wordlen;
    int m = B->wordlen;

    word w_Q;  // WORD 단위 Q. 실제로는 워드길이가 1인 구조체 Q와 R 을 반환한다.

    if(n == m)
        w_Q = A->a[n-1] / B->a[m-1];
    
    if(n == m + 1)
        if(A->a[m] == B->a[m-1]) {
            w_Q = WORD_MASK;
        }
        else {
            w_Q = L_D_A(A->a[m], A->a[m], B->a[m-1]);
        }

        // R = A - BQ를 위한 구조체 생성
        bigint* Q_temp = NULL;
        bigint* R_temp = NULL;
        bigint* BQ_temp = NULL;
        bi_new(&Q_temp, 1);
        Q_temp->a[0] = w_Q;
        bi_mul(B, Q_temp, &BQ_temp);
        bi_sub(A, BQ_temp, &R_temp);
        // Q_hat 계산 완료


        // 근사시킨 Q_hat으로 Q를 구한다. 이를 위해 1 원소를 가지는 bignum을 생성
        bigint* R_temp2 = NULL;
        bi_assign(&R_temp2, R_temp);
        while(R_temp->sign == 1) {  // while R < 0 
            w_Q -= 1;   // Q = Q - 1;
            bi_add(R_temp2, B, &R_temp);    // R = R + B;
        }


    // 워드길이가 1인 구조체 Q, R 반환
    (*Q)->a[0] = w_Q;
    bi_assign(R, R_temp);


    bi_delete(&Q_temp);
    bi_delete(&R_temp);
    bi_delete(&BQ_temp);
    bi_delete(&R_temp2);
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
            B_m1 = B_m1 << k;
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

    bi_set_zero(Q);
    bi_set_zero(R);

    int n = A->wordlen;
    int W = (1 << WORD_BITLEN); // 이러면 W?

    bigint* A_i = NULL;
    bigint* Q_i = NULL;
    bigint* R_temp = NULL;
    bi_set_zero(&A_i);
    bi_set_zero(&Q_i);
    for(int i = n - 1; i >= 0; i--) {
        Right_Shift(R, W);
        A_i->a[0] = A->a[i];
        Q_i->a[0] = (*Q)->a[i];
        bi_self_add(R, A_i);
        bi_assign(&R_temp, *R);
        bi_divc(R_temp, B, &Q_i, R);
        (*Q)->a[i] = Q_i->a[0];
    }

    bi_delete(&A_i);
    bi_delete(&Q_i);
    bi_delete(&R_temp);
}

*/