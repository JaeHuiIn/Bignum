#include "bignum_mul.c"

// schoolbook division
void bi_sb_div(bigint* A, bigint* B, bigint** Q, bigint** R);

// schoolbook binary long division
void Binary_Long_Division(bigint* A, bigint* B, bigint** Q, bigint** R);

//word L_D_A(bigint* A, word B);  // Long Division Algorithm with 2 word
void L_D_A(bigint* A, word B, bigint** Q);
void bi_divcc(bigint* A, bigint* B, bigint** Q, bigint** R);

void bi_divc(bigint* A, bigint* B, bigint** Q, bigint** R);

void DIV(bigint* A, bigint* B, bigint** Q, bigint** R);