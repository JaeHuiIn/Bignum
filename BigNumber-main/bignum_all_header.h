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

//********************************************기본 함수********************************************
void array_init(word* a, int wordlen);

//*************************************
// bi_delete : 제거함수
// input     : 한 개의 bigint x
// output    : 아무것도 없는 한 개의 bigint x
//*************************************
void bi_delete(bigint** x);

//*************************************
// bi_new : 생성함수
// input  : 한 개의 bigint x와 한 개의 word base
// output : 한 개의 bigint x
//*************************************
void bi_new(bigint** x, int wordlen);

//*************************************
// bi_set_by_array   : 작성함수
// bi_set_by_string  : 작성함수
// input             : 한 개의 bigint x와 두 개의 int sign, wordlen(base)과 한 개의 word(char) a
// output            : bi_set_by_array -> bigint x에 부호는 sign, 길이는 wordlen인 a를 작성
// output            : bi_set_by_array -> bigint x에 부호는 sign인 base진수 a를 작성
//*************************************
void bi_set_by_array(bigint** x, int sign, word* a, int wordlen);
void bi_set_by_string(bigint** x, int sign, char* a, int base);

//*************************************
// bi_show   : 출력함수
// input     : 한 개의 bigint x와 한 개의 word base
// output    : bigint x를 base진수로 출력
//*************************************
void bi_show(bigint* x, word base);

//*************************************
// bi_refine   : 앞 자리 제거 함수 (x의 맨 앞의 0으로 된 word 제거)
// input       : 한 개의 bigint x
// output      : 한 개의 bigint x
//*************************************
void bi_refine(bigint* x);

//*************************************
// array_copy  : 복사 함수 (y에 x를 복사)
// input       : 두 개의 word x, y와 한 개의 int wordlen
// output      : 복사된 word y
//*************************************
void array_copy(word y[], word x[], int wordlen);

//*************************************
// bi_assign  : 복사 함수 (y에 x를 복사)
// input      : 두 개의 bigint x, y
// output     : 한 개의 bigint y
//*************************************
void bi_assign(bigint** y, bigint* x);

//*************************************
// array_rand  : 랜덤 생성 함수
// bi_gen_rand : 랜덤 생성 함수
// output      : 랜덤한 수
//*************************************
void array_rand(word* dst, int wordlen);
void bi_gen_rand(bigint** x, int sign, int wordlen);

//*************************************
// get_wordlen  : 확인 함수 (x의 길이를 확인하는 함수)
// get_bitlen   : 확인 함수 (x의 비트 길이를 확인하는 함수)
// input        : 한 개의 bigint x
// output       : x의 길이(비트 길이)
//*************************************
int get_wordlen(bigint* x);
int get_bitlen(bigint* x);

//*************************************
// get_jth_bit   : 확인 함수 (x의 j번째 비트 수를 확인하는 함수)
// input         : 한 개의 bigint x와 int j
// output        : 1 or 0
//*************************************
int get_jth_bit(bigint* x, int j);

//*************************************
// bi_get_sign   : 확인 함수 (x의 부호를 확인하는 함수)
// input         : 한 개의 bigint x
// output        : 음수면 NEGATIVE, 양수면 NON-NEGATIVE
//*************************************
int bi_get_sign(bigint* x);

//*************************************
// bi_flip_sign  : 변환 함수 (x를 -x로 만드는 함수)
// input         : 한 개의 bigint x
// output        : 한 개의 bigint x
//*************************************
void bi_flip_sign(bigint** x);

//*************************************
// bi_set_one  : 변환 함수 (x를 1로 만드는 함수)
// bi_set_zero : 변환 함수 (x를 0로 만드는 함수)
// input       : 한 개의 bigint x
// output      : 한 개의 bigint x
//*************************************
void bi_set_one(bigint** x);
void bi_set_zero(bigint** x);

//*************************************
// is_zero : 확인 함수 (x가 0인지 확인)
// is_one  : 확인 함수 (x가 1인지 확인)
// input   : 한 개의 bigint x
// output  : is_zero - 0이면 0, 아니면 1 출력, is_one - 1이면 1, 아니면 0출력
//*************************************
int is_zero(bigint* x);
int is_one(bigint* x);

//*************************************
// Compare_ABS : 비교 함수(A와 B를 비교하는 함수)
// input       : 두 개의 양의 bigint A, B
// output      : A가 더 크면 1, B가 더 크면 -1, 두 값이 같으면 0
//*************************************
int Compare_ABS(bigint* A, bigint* B);
//*************************************
// Compare_AB : 비교 함수(A와 B를 비교하는 함수)
// input      : 두 개의 bigint A, B
// output     : A가 더 크면 1, B가 더 크면 -1, 두 값이 같으면 0
//*************************************
int Compare_AB(bigint** A, bigint** B);

//*************************************
// Left_Shift  : 쉬프트 함수(A를 왼쪽으로 r번 이동한 결과를 A에 저장)
// Right_Shift : 쉬프트 함수(A를 오른쪽으로 r번 이동한 결과를 A에 저장)
// input       : 한 개의 bigint A와 한 개의 int r
// output      : 한 개의 bigint A
//*************************************
void Left_Shift(bigint** x, int r);
void Right_Shift(bigint** x, int r);

//*************************************
// Reduction : 모듈러 함수(A를 mod 2^r한 결과를 A에 저장)
// input     : 한 개의 bigint A와 한 개의 int r
// output    : 한 개의 bigint A
//*************************************
void Reduction(bigint** A, int r);



//********************************************덧셈********************************************
//*************************************
// bi_add : 덧셈 함수 (x + y를 C에 저장)
// input  : 두 개의 bigint x, y
// output : 한 개의 bigint C
//*************************************
void bi_add(bigint* x, bigint* y, bigint** C);

//*************************************
// bi_self_add : 덧셈 함수 (x + y를 x에 저장)
// input       : 두 개의 bigint x, y
// output      : 한 개의 bigint x
//*************************************
void bi_self_add(bigint** x, bigint* y);




//********************************************뺄셈********************************************
//*************************************
// bi_subc : 뺄셈 함수 (x - y (x >= y > 0)를 C에 저장)
// input   : 두 개의 bigint x, y
// output  : 한 개의 bigint C
//*************************************
void bi_subc(bigint* x, bigint* y, bigint** C);

//*************************************
// bi_sub : 뺄셈 함수 (x - y를 C에 저장)
// input  : 두 개의 bigint x, y
// output : 한 개의 bigint C
//*************************************
void bi_sub(bigint* x, bigint* y, bigint** C);

//*************************************
// bi_self_sub : 뺄셈 함수 (x - y를 x에 저장)
// input       : 두 개의 bigint x, y
// output      : 한 개의 bigint x
//*************************************
void bi_self_sub(bigint** x, bigint* y);




//********************************************곱셈********************************************
//*************************************
// bi_mulc : 곱셈 함수 (x * y를 C에 저장)
// input   : 두 개의 word x, y
// output  : 한 개의 bigint C
//*************************************
void bi_mulc(word x, word y, bigint** C);

//*************************************
// bi_mul : 곱셈 함수 (x * y를 C에 저장)
// input  : 두 개의 bigint x, y
// output : 한 개의 bigint C
//*************************************
void bi_mul(bigint* x, bigint* y, bigint** C);

//*************************************
// bi_self_mul : 곱셈 함수 (x * y를 x에 저장)
// input       : 두 개의 bigint x, y
// output      : 한 개의 bigint x
//*************************************
void bi_self_mul(bigint** x, bigint* y);

//*************************************
// bi_kmul : 카라츄바 곱셈 함수 (x * y를 C에 저장)
// input   : 두 개의 양수 bigint x, y와 한 개의 int flag
// output  : 한 개의 bigint C
//*************************************
void bi_kmul(bigint* x, bigint* y, bigint** C, int flag);

//*************************************
// bi_kmulc : 카라츄바 곱셈 함수 (x * y를 C에 저장)
// input    : 두 개의 bigint x, y
// output   : 한 개의 bigint C
//*************************************
void bi_kmulc(bigint* x, bigint* y, bigint** C);

//*************************************
// bi_squaringC : 제곱 함수 (x^2를 C에 저장)
// input        : 한 개의 word x
// output       : 한 개의 bigint C
//*************************************
void bi_squaringC(word x, bigint** C);

//*************************************
// bi_squaringC : 제곱 함수 (x^2를 C에 저장)
// input        : 한 개의 bigint x
// output       : 한 개의 bigint C
//*************************************
void bi_squaring(bigint* x, bigint** C);

//*************************************
// bi_kmul : 카라츄바 제곱 함수 (x^2를 C에 저장)
// input   : 한 개의 양수 bigint x와 한 개의 int flag
// output  : 한 개의 bigint C
//*************************************
void bi_ksquaring(bigint* x, bigint** C, int flag);

//*************************************
// bi_kmul : 카라츄바 제곱 함수 (x^2를 C에 저장)
// input   : 한 개의 bigint x
// output  : 한 개의 bigint C
//*************************************
void bi_ksquaringC(bigint* x, bigint** C);




//********************************************나눗셈********************************************
//*************************************
// bi_sb_div : 나눗셈 함수 ( A를 B로 나눈 몫을 Q, 나머지를 R에 저장)
// input     : 네 개의 bigint A, B, Q, R (A >= 0, B > 0)
// output    : 두 개의 bigint Q, R (0 <= R < B)
//*************************************
void bi_sb_div(bigint* A, bigint* B, bigint** Q, bigint** R);

//*************************************
// Binary_Long_Division : 나눗셈 함수 ( A를 B로 나눈 몫을 Q, 나머지를 R에 저장)
// input     : 네 개의 bigint A, B, Q, R (A >= B > 0)
// output    : 두 개의 bigint Q, R (0 <= R < B)
//*************************************
void Binary_Long_Division(bigint* A, bigint* B, bigint** Q, bigint** R);

//*************************************
// L_D_A  : 나눗셈 함수 (A를 B로 나눈 몫을 Q에 저장)
// input  : 두 개의 bigint A, Q와 한 개의 word B 
// output : 두 개의 bigint Q, R (0 <= R < B)
//*************************************
void L_D_A(bigint* A, word B, bigint** Q);

//*************************************
// bi_divcc : 나눗셈 함수 (A를 B로 나눈 몫을 Q, 나머지를 R에 저장)
// input    : 네 개의 bigint A, B, Q, R (A, B >= 0, 0 < B <= A < 1 Word * B)
// output   : 두 개의 bigint Q, R (0 <= R < B, 0 <= Q < 1 Word)
//*************************************
void bi_divcc(bigint* A, bigint* B, bigint** Q, bigint** R);

//*************************************
// bi_divc : 나눗셈 함수 (A를 B로 나눈 몫을 Q, 나머지를 R에 저장)
// input   : 네 개의 bigint A, B, Q, R (A, B >= 0, 0 <= A < 1 Word * B)
// output  : 두 개의 bigint Q, R (0 <= R < B, 0 <= Q < 1 Word)
//*************************************
void bi_divc(bigint* A, bigint* B, bigint** Q, bigint** R);

//*************************************
// DIV    : 나눗셈 함수 ( A를 B로 나눈 몫을 Q, 나머지를 R에 저장)
// input  : 네 개의 bigint A, B, Q, R (A, B > 0)
// output : 두 개의 bigint Q, R (0 <= R < B)
//*************************************
void DIV(bigint* A, bigint* B, bigint** Q, bigint** R);




//********************************************지수승********************************************
//*************************************
// ModExp_LTR  : 지수승 함수 ( x의 n제곱을 mod N 한 결과를 x에 저장)
// input       : 세 개의 bigint x, n, N
// output      : 한 개의 bigint x
//*************************************
void ModExp_LTR(bigint** x, bigint* n, bigint* N);

//*************************************
// ModExp_RTL  : 지수승 함수 ( x의 n제곱을 mod N 한 결과를 x에 저장)
// input       : 세 개의 bigint x, n, N
// output      : 한 개의 bigint x
//*************************************
void ModExp_RTL(bigint** x, bigint* n, bigint* N);

//*************************************
// ModExp_Montgomery : 지수승 함수 ( x의 n제곱을 mod N 한 결과를 x에 저장)
// input             : 세 개의 bigint x, n, N
// output            : 한 개의 bigint x
//*************************************
void ModExp_Montgomery(bigint** x, bigint* n, bigint* N);



//********************************************테스트 함수********************************************
// 여기부턴 쓸 내용있으면 첨가
void bignumber_test();

void speed_check();
void accuracy_check();
void calculate_bignumber();

//*************************************
// add_speed                     : 덧셈의 속도를 측정하는 함수
// sub_speed                     : 뺄셈의 속도를 측정하는 함수
// schoolbook_mul_speed          : 곱셈의 속도를 측정하는 함수
// karatsuba_mul_speed           : 카라츄바 곱셈의 속도를 측정하는 함수
// Schoolbook_Squaring_speed     : 제곱의 속도를 측정하는 함수
// Karatsuba_Squaring_speed      : 카라츄바 제곱의 속도를 측정하는 함수
// Binary_Long_Division_speed    : Binary_Long_Division의 속도를 측정하는 함수
// Multiprecision_Division_speed : Multiprecision_Division의 속도를 측정하는 함수
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
// basic_test    : 기본 함수를 확인하는 함수
// add_test      : 덧셈 함수를 확인하는 함수
// sub_test      : 뺄셈 함수를 확인하는 함수
// mul_test      : 곱셈 함수를 확인하는 함수
// div_test      : 나눗셈 함수를 확인하는 함수
// mod_exp_test  : 지수승 함수를 확인하는 함수
//*************************************
void basic_test();
void add_test();
void sub_test();
void mul_test();
void div_test();
void mod_exp_test();

//*************************************
// calculate_add     : 덧셈 함수에 원하는 수를 넣는 함수
// calculate_sub     : 뺄셈 함수에 원하는 수를 넣는 함수
// calculate_mul     : 곱셈 함수에 원하는 수를 넣는 함수
// calculate_div     : 나눗셈 함수에 원하는 수를 넣는 함수
// calculate_mod_exp : 지수승 함수에 원하는 수를 넣는 함수
//*************************************
void calculate_add();
void calculate_sub();
void calculate_mul();
void calculate_div();
void calculate_mod_exp();
