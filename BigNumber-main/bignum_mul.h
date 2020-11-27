#include "bignum_add_sub.c"

void bi_mulc(word x, word y, bigint** C);
void bi_mul(bigint* x, bigint* y, bigint** C);
void bi_kmul(bigint* x, bigint* y, bigint** C, int flag);
void bi_kmulc(bigint* x, bigint* y, bigint** C);
void bi_squareC(word x, bigint** C);
void bi_square(bigint* x, bigint** C);
void bi_ksquaring(bigint* x, bigint** C, int flag);
void bi_ksquaringC(bigint* x, bigint** C);