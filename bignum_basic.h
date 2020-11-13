#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define WORD_BITLEN 32

#if WORD_BITLEN == 8
typedef unsigned char word;
word arr[3] = { 0x12, 0x34, 0x56 };
#elif WORD_BITLEN == 32
typedef unsigned int word;
word arr[3] = { 0x12345678, 0x9abc0123, 0x456789ab };
#elif WORD_BITLEN == 64
typedef unsigned long long word;
word arr[3] = { 0x123456789abcdef, 0x9abcedf012345678, 0xdef0123456789abc };
#endif 

#define NON_NEGATIVE 0
#define NEGATIVE 1

#define ZERORIZE 0

/* Dynamic Memory Allocation */
typedef struct {

	int sign;       // NEGATIVE or NON-NEGATIVE
	int wordlen;    // wordlen >= 0
	word* a;        // address for big integer
} bigint;

void array_init(word* a, int wordlen);

/* 2.1 Create BigInt, Delete BigInt, Zeroize BigInt */
void bi_delete(bigint** x);
void bi_new(bigint** x, int wordlen);

/* 2.2 Set BigInt, Show BigInt */
void bi_set_by_array(bigint** x, int sign, word* a, int wordlen);   // bigint x <- sign and array a
void bi_show(bigint* x, word base);

/* 2.3 Refine BigInt (Remove Last Zero Words) */
void bi_refine(bigint* x);

/* 2.4 Assign BigInt */
void array_copy(word y[], word x[], int wordlen);
void bi_assign(bigint** y, bigint* x);

/* 2.5 Generate Random BigInt */
void array_rand(word* dst, int wordlen);
void bi_gen_rand(bigint** x, int sign, int wordlen);

/* 2.6 Get Word Lengh / Bit Length / j-th Bit of BigInt */
int get_wordlen(bigint* x);
int get_bitlen(bigint* x);
int get_jth_bit(bigint* x, int j);

/* 2.7 Get Sign and Flip Sign of BigInt */
int bi_get_sign(bigint* x);
void bi_flip_sign(bigint** x);

/* 2.8 Set One, Set Zero, Is Zero, Is One */
void bi_set_one(bigint** x);
void bi_set_zero(bigint** x);
int is_zero(bigint* x);  // 0이면 0을, 0이 아니면 1을 반환한다.
int is_one(bigint* x);  // 1이면 1, 1이 아니면 0을 반환한다.

/* 2.9 Compare ABS, Compare AB*/
int Compare_ABS(bigint* A, bigint* B); // 음이 아닌 정수 A, B의 대수 비교. A > B : 1 리턴, A = B : 0 리턴, A < B : -1 리턴 
int Compare_AB(bigint** A, bigint** B);

/* 2.10 Left / Right Shift */
void Left_Shift(bigint** x, int r);
void Right_Shift(bigint** x, int r);

/* 2.11 Reduction */
void Reduction(bigint** A, int r);




















