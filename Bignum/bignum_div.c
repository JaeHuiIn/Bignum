#include "bignum_div.h"

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
            w_Q = (A->a[m] * sizeof(word) + A->a[m-1]) / B->a[m-1]; 
            // Pseudo Code의 line 8
            // 우선, Q는 word이다. 그런데 W와 A[m]을 곱할때 W를 넘어갈수도 있는데, 상관이 없는 부분인가?
            // ㄴㄴ 강의노트 보니까 LINE 8 부분은  binary long division with 2 word로 구현해야함. 97페이지 참고!
            // 나중에 구현 ㄱㄱ
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

    
}