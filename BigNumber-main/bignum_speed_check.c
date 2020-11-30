#include "bignum_all_header.h"

// clock_t start = clock();
// clock_t end = clock();
// printf("Time : %lf\n", (double)(end - start) / CLOCKS_PER_SEC);


void add_speed()
{

    int check;  // 테스트 데이터 쌍 개수
    int first_number_wordlen;   // 첫번째 bigint의 워드길이
    int second_number_wordlen;  // 두번째 bigint의 워드길이

    printf("Enter number for checks: ");
    scanf("%d", &check);
    
    bigint* A = NULL;
    bigint* B = NULL;
    bigint* C = NULL;
    bi_gen_rand(&A, 0, 10);
    bi_gen_rand(&B, 0, 10);


    clock_t start, end; // 시간 측정용 변수
    double times = 0;   // 실행 시간의 합

    start = clock();    // 측정 시작
    for(int i = 0; i < check / 3; i++){
        bi_add(A, B, &C);   // 함수 실행

        bi_add(C, A, &B);

        bi_add(B, C, &A);
    }
    end = clock();      // 측정 종료

    printf("Add function Time: %lf\n", (double)(end - start) / CLOCKS_PER_SEC);

    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&C);

}