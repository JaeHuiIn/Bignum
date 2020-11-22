#include "bignum_mul.c"

//word L_D_A(bigint* A, word B);  // Long Division Algorithm with 2 word
void L_D_A(bigint* A, word B, bigint** Q);
void bi_divcc(bigint* A, bigint* B, bigint** Q, bigint** R);

void bi_divc(bigint* A, bigint* B, bigint** Q, bigint** R);

void DIV(bigint* A, bigint* B, bigint** Q, bigint** R);