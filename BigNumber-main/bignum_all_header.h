#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "config.h"

#define NON_NEGATIVE 0
#define NEGATIVE 1


typedef struct {

	int sign;
	int wordlen;
	word* a;
} bigint;

void array_init(word* a, int wordlen);


void bi_delete(bigint** x);
void bi_new(bigint** x, int wordlen);


void bi_set_by_array(bigint** x, int sign, word* a, int wordlen);
void bi_set_by_string(bigint** x, int sign, char* a, int base);
void bi_show(bigint* x, word base);


void bi_refine(bigint* x);


void array_copy(word y[], word x[], int wordlen);
void bi_assign(bigint** y, bigint* x);


void array_rand(word* dst, int wordlen);
void bi_gen_rand(bigint** x, int sign, int wordlen);


int get_wordlen(bigint* x);
int get_bitlen(bigint* x);
int get_jth_bit(bigint* x, int j);


int bi_get_sign(bigint* x);
void bi_flip_sign(bigint** x);


void bi_set_one(bigint** x);
void bi_set_zero(bigint** x);
int is_zero(bigint* x);
int is_one(bigint* x);


int Compare_ABS(bigint* A, bigint* B);
int Compare_AB(bigint** A, bigint** B);


void Left_Shift(bigint** x, int r);
void Right_Shift(bigint** x, int r);


void Reduction(bigint** A, int r);


void bi_add(bigint* x, bigint* y, bigint** C);
void bi_self_add(bigint** x, bigint* y);


void bi_subc(bigint* x, bigint* y, bigint** C);
void bi_sub(bigint* x, bigint* y, bigint** C);
void bi_self_sub(bigint** x, bigint* y);

void bi_mulc(word x, word y, bigint** C);
void bi_mul(bigint* x, bigint* y, bigint** C);
void bi_kmul(bigint* x, bigint* y, bigint** C, int flag);
void bi_kmulc(bigint* x, bigint* y, bigint** C);
void bi_squareC(word x, bigint** C);
void bi_square(bigint* x, bigint** C);
void bi_squaring(bigint* x, bigint** C);
void bi_ksquaring(bigint* x, bigint** C, int flag);
void bi_ksquaringC(bigint* x, bigint** C);
void bi_self_mul(bigint** x, bigint* y);

void bi_sb_div(bigint* A, bigint* B, bigint** Q, bigint** R);
void Binary_Long_Division(bigint* A, bigint* B, bigint** Q, bigint** R);
void L_D_A(bigint* A, word B, bigint** Q);
void bi_divcc(bigint* A, bigint* B, bigint** Q, bigint** R);
void bi_divc(bigint* A, bigint* B, bigint** Q, bigint** R);
void DIV(bigint* A, bigint* B, bigint** Q, bigint** R);


void ModExp_LTR(bigint** x, bigint* n, bigint* N);
void ModExp_RTL(bigint** x, bigint* n, bigint* N);
void ModExp_Montgomery(bigint** x, bigint* n, bigint* N);



void basic_test();
void add_test();
void sub_test();
void mul_test();
void div_test();
void mod_exp_test();





void add_speed();
void sub_speed();
void schoolbook_mul_speed();
void karatsuba_mul_speed();
void Schoolbook_Squaring_speed();
void Karatsuba_Squaring_speed();
void Binary_Long_Division_speed();
void Multiprecision_Division_speed();


