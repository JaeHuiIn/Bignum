/**
 * Big Number Library
 * Developed by JangHyuck Choi & JaeHui In 
 * 2020-11-02
 * */

#include "bignum_mul.c"

int main()
{
	bigint* teemo = NULL;

	printf("create big int\n");
	bi_new(&teemo, 3);
	printf("created\n\n");

	printf("set by array\n");
	bi_set_by_array(&teemo, teemo->sign, arr, teemo->wordlen);
	printf("set completed\n\n");

	printf("show big int\n");
	printf("show by base 2: ");
	bi_show(teemo, 2);
	printf("\n");
	// printf("show by base 10: \n");   // ADD, MUL 구현 이후 제작할 예정
	// bi_show(teemo, 10);
	printf("show by base 16: ");
	bi_show(teemo, 16);
	printf("\n\n");

	// printf("bi_refine: \n");

	printf("Assign big int A <-- B \n");
	printf("show big int B: ");
	bi_show(teemo, 16);
	printf("\n");
	bigint* teemo2 = NULL;
	bi_assign(&teemo2, teemo);
	printf("show assigned big int A: ");
	bi_show(teemo2, 16);
	printf("\n\n");

	printf("get word length: ");
	int wordlen = get_wordlen(teemo);
	printf("%d", wordlen);
	printf("\n");

	printf("get bit length: ");
	int bitlen = get_bitlen(teemo);
	printf("%d\n", bitlen);
	printf("\n");

	printf("generate random bigint: ");
	bigint* teemo3 = NULL;
	bi_gen_rand(&teemo3, NON_NEGATIVE, 3); // wordlen 3인 양수의 랜덤 big int 생성
	bi_show(teemo3, 2);
	printf("\n\n");
	bi_show(teemo3, 16);
	printf("\n\n");

	printf("get j-th bit \n");
	// printf("enter j: ");
	int j_th = 4;
	// scanf("%d\n", j);
	int j = get_jth_bit(teemo, j_th);
	// j가 비트 길이를 넘어서면 에러 메세지를 출력해야 함 --> 구현 필요
	printf("%d-th bit: %d\n\n", j_th, j);

	printf("get sign and flip sign of big int\n");
	printf("sign of big int: %d\n", bi_get_sign(teemo));
	bi_flip_sign(&teemo);
	printf("flipped sign: %d\n\n", bi_get_sign(teemo));

	printf("big int set one, is one\n");
	bigint* teemo4 = NULL;
	bi_assign(&teemo4, teemo);
	printf("before set one: ");
	bi_show(teemo4, 16);
	printf("\n\n");
	printf("is big int one: %d\n", is_one(teemo4));
	printf("after set one: ");
	bi_set_one(&teemo4);
	bi_show(teemo4, 16);
	printf("\n\n");
	printf("is big int one: %d\n\n", is_one(teemo4));

	printf("big int set zero, is zero\n");
	bigint* teemo5 = NULL;
	bi_assign(&teemo5, teemo4);
	printf("before set zero: ");
	bi_show(teemo5, 16);
	printf("\n");
	printf("is big int zero: %d\n", is_zero(teemo5));
	printf("after set zero: ");
	bi_set_zero(&teemo5);
	bi_show(teemo5, 16);
	printf("\n");
	printf("is big int zero: %d\n\n", is_zero(teemo5));

	printf("compare big int\n");
	printf("big int A = ");
	bi_show(teemo4, 16);
	printf("big int B = ");
	bi_show(teemo5, 16);
	printf("print 1 if A > B: %d\n\n", Compare_AB(&teemo4, &teemo5));


	printf("left shift\nbefore left shift: ");
	bi_show(teemo4, 16);
	printf("\n");
	printf("after shift 4 bit: ");
	Left_Shift(&teemo4, 23);
	bi_show(teemo4, 16);
	printf("\n\n");

	printf("right shift\nbefore right shift: ");
	bi_show(teemo3, 16);
	printf("\n");
	printf("after shift 4 bit: ");
	Right_Shift(&teemo3, 24);
	bi_show(teemo3, 16);
	printf("\n\n");


	printf("big int reduction\nbefore reduction: ");
	Left_Shift(&teemo3, 4);
	bi_show(teemo3, 16);
	printf("\n");
	printf("after reduction by 2^4: ");
	Reduction(&teemo3, 15);
	bi_show(teemo3, 16);
	printf("\n\n");
	
	

	word arr1[2] = {0x11111111, 0x22222222};
	word arr2[2] = {0x10000000, 0x11111111};
	bigint* add_teemo1 = NULL;
	bigint* add_teemo2 = NULL;
	bigint* add_teemo3 = NULL;
	bigint* sub_teemo1 = NULL;
	bigint* sub_teemo2 = NULL;
	bigint* sub_teemo3 = NULL;
	bi_new(&add_teemo1, 2);
	bi_new(&add_teemo2, 2);
	bi_new(&sub_teemo1, 2);
	bi_new(&sub_teemo2, 2);
	bi_set_by_array(&add_teemo1, add_teemo1->sign, arr1, add_teemo1->wordlen);
	bi_set_by_array(&add_teemo2, add_teemo2->sign, arr2, add_teemo2->wordlen);
	bi_set_by_array(&sub_teemo1, sub_teemo1->sign, arr1, sub_teemo1->wordlen);
	bi_set_by_array(&sub_teemo2, sub_teemo2->sign, arr2, sub_teemo2->wordlen);	
	
	printf("big int add\nA: ");	
	bi_show(add_teemo1, 16);
	printf("\n");
	printf("B: ");
	bi_show(add_teemo2, 16);
	printf("\n");
	bi_add(add_teemo1, add_teemo2, &add_teemo3);	
	printf("A + B = ");
	bi_show(add_teemo3, 16);
	printf("\n\n");

	printf("big int sub\nC: ");	
	bi_show(sub_teemo1, 16);
	printf("\n");
	printf("D: ");
	bi_show(sub_teemo2, 16);
	printf("\n");
	bi_sub(sub_teemo1, sub_teemo2, &sub_teemo3);	
	printf("A - B = ");
	bi_show(sub_teemo3, 16);
	printf("\n\n");

	printf("#big int mul(single pricision)\n");
	bigint* SP_mul_teemo = NULL;
	bi_mulc(arr[0], arr[1], &SP_mul_teemo);
	printf("print(x*y == 0x");
	bi_show(SP_mul_teemo, 16);
	printf(")\n\n");

	printf("#big int mul(multi pricision, Schoolbook)\n");
	bigint* mul_teemo = NULL;
	bi_flip_sign(&teemo);
	bi_mul(teemo, teemo3, &mul_teemo);
	printf("x = 0x");
	bi_show(teemo, 16);
	printf("\n");
	printf("y = 0x");
	bi_show(teemo3, 16);
	printf("\n");
	bi_mul(teemo, teemo3, &mul_teemo);
	printf("print(x*y == 0x");
	bi_show(mul_teemo, 16);
	printf(")\n\n");

	printf("#big int mul(multi pricision, Karatsuba)\n");
	bigint* mul_K_teemo = NULL;
	bi_kmul(teemo, teemo3, &mul_K_teemo);
	printf("x = 0x");
	bi_show(teemo, 16);
	printf("\n");
	printf("y = 0x");
	bi_show(teemo3, 16);
	printf("\n");
	printf("print(x*y == 0x");
	bi_show(mul_K_teemo, 16);
	printf(")\n\n");

	bi_delete(&teemo);
	bi_delete(&teemo2);
	bi_delete(&teemo3);
	bi_delete(&teemo4);
	bi_delete(&teemo5);
	bi_delete(&add_teemo1);
	bi_delete(&add_teemo2);
	bi_delete(&add_teemo3);
	bi_delete(&sub_teemo1);
	bi_delete(&sub_teemo2);
	bi_delete(&sub_teemo3);
	bi_delete(&SP_mul_teemo);
	bi_delete(&mul_teemo);
	bi_delete(&mul_K_teemo);

	return 0;
}