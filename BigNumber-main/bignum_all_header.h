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

//********************************************�⺻ �Լ�********************************************
void array_init(word* a, int wordlen);

//*************************************
// bi_delete : �����Լ�
// input     : �� ���� bigint x
// output    : �ƹ��͵� ���� �� ���� bigint x
//*************************************
void bi_delete(bigint** x);

//*************************************
// bi_new : �����Լ�
// input  : �� ���� bigint x�� �� ���� word base
// output : �� ���� bigint x
//*************************************
void bi_new(bigint** x, int wordlen);

//*************************************
// bi_set_by_array   : �ۼ��Լ�
// bi_set_by_string  : �ۼ��Լ�
// input             : �� ���� bigint x�� �� ���� int sign, wordlen(base)�� �� ���� word(char) a
// output            : bi_set_by_array -> bigint x�� ��ȣ�� sign, ���̴� wordlen�� a�� �ۼ�
// output            : bi_set_by_array -> bigint x�� ��ȣ�� sign�� base���� a�� �ۼ�
//*************************************
void bi_set_by_array(bigint** x, int sign, word* a, int wordlen);
void bi_set_by_string(bigint** x, int sign, char* a, int base);

//*************************************
// bi_show   : ����Լ�
// input     : �� ���� bigint x�� �� ���� word base
// output    : bigint x�� base������ ���
//*************************************
void bi_show(bigint* x, word base);

//*************************************
// bi_refine   : �� �ڸ� ���� �Լ� (x�� �� ���� 0���� �� word ����)
// input       : �� ���� bigint x
// output      : �� ���� bigint x
//*************************************
void bi_refine(bigint* x);

//*************************************
// array_copy  : ���� �Լ� (y�� x�� ����)
// input       : �� ���� word x, y�� �� ���� int wordlen
// output      : ����� word y
//*************************************
void array_copy(word y[], word x[], int wordlen);

//*************************************
// bi_assign  : ���� �Լ� (y�� x�� ����)
// input      : �� ���� bigint x, y
// output     : �� ���� bigint y
//*************************************
void bi_assign(bigint** y, bigint* x);

//*************************************
// array_rand  : ���� ���� �Լ�
// bi_gen_rand : ���� ���� �Լ�
// output      : ������ ��
//*************************************
void array_rand(word* dst, int wordlen);
void bi_gen_rand(bigint** x, int sign, int wordlen);

//*************************************
// get_wordlen  : Ȯ�� �Լ� (x�� ���̸� Ȯ���ϴ� �Լ�)
// get_bitlen   : Ȯ�� �Լ� (x�� ��Ʈ ���̸� Ȯ���ϴ� �Լ�)
// input        : �� ���� bigint x
// output       : x�� ����(��Ʈ ����)
//*************************************
int get_wordlen(bigint* x);
int get_bitlen(bigint* x);

//*************************************
// get_jth_bit   : Ȯ�� �Լ� (x�� j��° ��Ʈ ���� Ȯ���ϴ� �Լ�)
// input         : �� ���� bigint x�� int j
// output        : 1 or 0
//*************************************
int get_jth_bit(bigint* x, int j);

//*************************************
// bi_get_sign   : Ȯ�� �Լ� (x�� ��ȣ�� Ȯ���ϴ� �Լ�)
// input         : �� ���� bigint x
// output        : ������ NEGATIVE, ����� NON-NEGATIVE
//*************************************
int bi_get_sign(bigint* x);

//*************************************
// bi_flip_sign  : ��ȯ �Լ� (x�� -x�� ����� �Լ�)
// input         : �� ���� bigint x
// output        : �� ���� bigint x
//*************************************
void bi_flip_sign(bigint** x);

//*************************************
// bi_set_one  : ��ȯ �Լ� (x�� 1�� ����� �Լ�)
// bi_set_zero : ��ȯ �Լ� (x�� 0�� ����� �Լ�)
// input       : �� ���� bigint x
// output      : �� ���� bigint x
//*************************************
void bi_set_one(bigint** x);
void bi_set_zero(bigint** x);

//*************************************
// is_zero : Ȯ�� �Լ� (x�� 0���� Ȯ��)
// is_one  : Ȯ�� �Լ� (x�� 1���� Ȯ��)
// input   : �� ���� bigint x
// output  : is_zero - 0�̸� 0, �ƴϸ� 1 ���, is_one - 1�̸� 1, �ƴϸ� 0���
//*************************************
int is_zero(bigint* x);
int is_one(bigint* x);

//*************************************
// Compare_ABS : �� �Լ�(A�� B�� ���ϴ� �Լ�)
// input       : �� ���� ���� bigint A, B
// output      : A�� �� ũ�� 1, B�� �� ũ�� -1, �� ���� ������ 0
//*************************************
int Compare_ABS(bigint* A, bigint* B);
//*************************************
// Compare_AB : �� �Լ�(A�� B�� ���ϴ� �Լ�)
// input      : �� ���� bigint A, B
// output     : A�� �� ũ�� 1, B�� �� ũ�� -1, �� ���� ������ 0
//*************************************
int Compare_AB(bigint** A, bigint** B);

//*************************************
// Left_Shift  : ����Ʈ �Լ�(A�� �������� r�� �̵��� ����� A�� ����)
// Right_Shift : ����Ʈ �Լ�(A�� ���������� r�� �̵��� ����� A�� ����)
// input       : �� ���� bigint A�� �� ���� int r
// output      : �� ���� bigint A
//*************************************
void Left_Shift(bigint** x, int r);
void Right_Shift(bigint** x, int r);

//*************************************
// Reduction : ��ⷯ �Լ�(A�� mod 2^r�� ����� A�� ����)
// input     : �� ���� bigint A�� �� ���� int r
// output    : �� ���� bigint A
//*************************************
void Reduction(bigint** A, int r);



//********************************************����********************************************
//*************************************
// bi_add : ���� �Լ� (x + y�� C�� ����)
// input  : �� ���� bigint x, y
// output : �� ���� bigint C
//*************************************
void bi_add(bigint* x, bigint* y, bigint** C);

//*************************************
// bi_self_add : ���� �Լ� (x + y�� x�� ����)
// input       : �� ���� bigint x, y
// output      : �� ���� bigint x
//*************************************
void bi_self_add(bigint** x, bigint* y);




//********************************************����********************************************
//*************************************
// bi_subc : ���� �Լ� (x - y (x >= y > 0)�� C�� ����)
// input   : �� ���� bigint x, y
// output  : �� ���� bigint C
//*************************************
void bi_subc(bigint* x, bigint* y, bigint** C);

//*************************************
// bi_sub : ���� �Լ� (x - y�� C�� ����)
// input  : �� ���� bigint x, y
// output : �� ���� bigint C
//*************************************
void bi_sub(bigint* x, bigint* y, bigint** C);

//*************************************
// bi_self_sub : ���� �Լ� (x - y�� x�� ����)
// input       : �� ���� bigint x, y
// output      : �� ���� bigint x
//*************************************
void bi_self_sub(bigint** x, bigint* y);




//********************************************����********************************************
//*************************************
// bi_mulc : ���� �Լ� (x * y�� C�� ����)
// input   : �� ���� word x, y
// output  : �� ���� bigint C
//*************************************
void bi_mulc(word x, word y, bigint** C);

//*************************************
// bi_mul : ���� �Լ� (x * y�� C�� ����)
// input  : �� ���� bigint x, y
// output : �� ���� bigint C
//*************************************
void bi_mul(bigint* x, bigint* y, bigint** C);

//*************************************
// bi_self_mul : ���� �Լ� (x * y�� x�� ����)
// input       : �� ���� bigint x, y
// output      : �� ���� bigint x
//*************************************
void bi_self_mul(bigint** x, bigint* y);

//*************************************
// bi_kmul : ī����� ���� �Լ� (x * y�� C�� ����)
// input   : �� ���� ��� bigint x, y�� �� ���� int flag
// output  : �� ���� bigint C
//*************************************
void bi_kmul(bigint* x, bigint* y, bigint** C, int flag);

//*************************************
// bi_kmulc : ī����� ���� �Լ� (x * y�� C�� ����)
// input    : �� ���� bigint x, y
// output   : �� ���� bigint C
//*************************************
void bi_kmulc(bigint* x, bigint* y, bigint** C);

//*************************************
// bi_squaringC : ���� �Լ� (x^2�� C�� ����)
// input        : �� ���� word x
// output       : �� ���� bigint C
//*************************************
void bi_squaringC(word x, bigint** C);

//*************************************
// bi_squaringC : ���� �Լ� (x^2�� C�� ����)
// input        : �� ���� bigint x
// output       : �� ���� bigint C
//*************************************
void bi_squaring(bigint* x, bigint** C);

//*************************************
// bi_kmul : ī����� ���� �Լ� (x^2�� C�� ����)
// input   : �� ���� ��� bigint x�� �� ���� int flag
// output  : �� ���� bigint C
//*************************************
void bi_ksquaring(bigint* x, bigint** C, int flag);

//*************************************
// bi_kmul : ī����� ���� �Լ� (x^2�� C�� ����)
// input   : �� ���� bigint x
// output  : �� ���� bigint C
//*************************************
void bi_ksquaringC(bigint* x, bigint** C);




//********************************************������********************************************
//*************************************
// bi_sb_div : ������ �Լ� ( A�� B�� ���� ���� Q, �������� R�� ����)
// input     : �� ���� bigint A, B, Q, R (A >= 0, B > 0)
// output    : �� ���� bigint Q, R (0 <= R < B)
//*************************************
void bi_sb_div(bigint* A, bigint* B, bigint** Q, bigint** R);

//*************************************
// Binary_Long_Division : ������ �Լ� ( A�� B�� ���� ���� Q, �������� R�� ����)
// input     : �� ���� bigint A, B, Q, R (A >= B > 0)
// output    : �� ���� bigint Q, R (0 <= R < B)
//*************************************
void Binary_Long_Division(bigint* A, bigint* B, bigint** Q, bigint** R);

//*************************************
// L_D_A  : ������ �Լ� (A�� B�� ���� ���� Q�� ����)
// input  : �� ���� bigint A, Q�� �� ���� word B 
// output : �� ���� bigint Q, R (0 <= R < B)
//*************************************
void L_D_A(bigint* A, word B, bigint** Q);

//*************************************
// bi_divcc : ������ �Լ� (A�� B�� ���� ���� Q, �������� R�� ����)
// input    : �� ���� bigint A, B, Q, R (A, B >= 0, 0 < B <= A < 1 Word * B)
// output   : �� ���� bigint Q, R (0 <= R < B, 0 <= Q < 1 Word)
//*************************************
void bi_divcc(bigint* A, bigint* B, bigint** Q, bigint** R);

//*************************************
// bi_divc : ������ �Լ� (A�� B�� ���� ���� Q, �������� R�� ����)
// input   : �� ���� bigint A, B, Q, R (A, B >= 0, 0 <= A < 1 Word * B)
// output  : �� ���� bigint Q, R (0 <= R < B, 0 <= Q < 1 Word)
//*************************************
void bi_divc(bigint* A, bigint* B, bigint** Q, bigint** R);

//*************************************
// DIV    : ������ �Լ� ( A�� B�� ���� ���� Q, �������� R�� ����)
// input  : �� ���� bigint A, B, Q, R (A, B > 0)
// output : �� ���� bigint Q, R (0 <= R < B)
//*************************************
void DIV(bigint* A, bigint* B, bigint** Q, bigint** R);




//********************************************������********************************************
//*************************************
// ModExp_LTR  : ������ �Լ� ( x�� n������ mod N �� ����� x�� ����)
// input       : �� ���� bigint x, n, N
// output      : �� ���� bigint x
//*************************************
void ModExp_LTR(bigint** x, bigint* n, bigint* N);

//*************************************
// ModExp_RTL  : ������ �Լ� ( x�� n������ mod N �� ����� x�� ����)
// input       : �� ���� bigint x, n, N
// output      : �� ���� bigint x
//*************************************
void ModExp_RTL(bigint** x, bigint* n, bigint* N);

//*************************************
// ModExp_Montgomery : ������ �Լ� ( x�� n������ mod N �� ����� x�� ����)
// input             : �� ���� bigint x, n, N
// output            : �� ���� bigint x
//*************************************
void ModExp_Montgomery(bigint** x, bigint* n, bigint* N);



//********************************************�׽�Ʈ �Լ�********************************************
// ������� �� ���������� ÷��
void bignumber_test();

void speed_check();
void accuracy_check();
void calculate_bignumber();

//*************************************
// add_speed                     : ������ �ӵ��� �����ϴ� �Լ�
// sub_speed                     : ������ �ӵ��� �����ϴ� �Լ�
// schoolbook_mul_speed          : ������ �ӵ��� �����ϴ� �Լ�
// karatsuba_mul_speed           : ī����� ������ �ӵ��� �����ϴ� �Լ�
// Schoolbook_Squaring_speed     : ������ �ӵ��� �����ϴ� �Լ�
// Karatsuba_Squaring_speed      : ī����� ������ �ӵ��� �����ϴ� �Լ�
// Binary_Long_Division_speed    : Binary_Long_Division�� �ӵ��� �����ϴ� �Լ�
// Multiprecision_Division_speed : Multiprecision_Division�� �ӵ��� �����ϴ� �Լ�
//*************************************
void add_speed();
void sub_speed();
void schoolbook_mul_speed();
void karatsuba_mul_speed();
void Schoolbook_Squaring_speed();
void Karatsuba_Squaring_speed();
void Binary_Long_Division_speed();
void Multiprecision_Division_speed();

//*************************************
// basic_test    : �⺻ �Լ��� Ȯ���ϴ� �Լ�
// add_test      : ���� �Լ��� Ȯ���ϴ� �Լ�
// sub_test      : ���� �Լ��� Ȯ���ϴ� �Լ�
// mul_test      : ���� �Լ��� Ȯ���ϴ� �Լ�
// div_test      : ������ �Լ��� Ȯ���ϴ� �Լ�
// mod_exp_test  : ������ �Լ��� Ȯ���ϴ� �Լ�
//*************************************
void basic_test();
void add_test();
void sub_test();
void mul_test();
void div_test();
void mod_exp_test();

//*************************************
// calculate_add     : ���� �Լ��� ���ϴ� ���� �ִ� �Լ�
// calculate_sub     : ���� �Լ��� ���ϴ� ���� �ִ� �Լ�
// calculate_mul     : ���� �Լ��� ���ϴ� ���� �ִ� �Լ�
// calculate_div     : ������ �Լ��� ���ϴ� ���� �ִ� �Լ�
// calculate_mod_exp : ������ �Լ��� ���ϴ� ���� �ִ� �Լ�
//*************************************
void calculate_add();
void calculate_sub();
void calculate_mul();
void calculate_div();
void calculate_mod_exp();
