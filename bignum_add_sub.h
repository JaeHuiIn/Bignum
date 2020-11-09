#include "bignum_basic.c"
// 덧셈, 뺄셈 구현

//bigint 덧셈
void bi_add(bigint* x, bigint* y, bigint** C);

// bigint 뺄셈
void bi_subc(bigint* x, bigint*y, bigint ** C);  // x >= y > 0 에서 x - y
void bi_sub(bigint* x, bigint*y, bigint** C);

