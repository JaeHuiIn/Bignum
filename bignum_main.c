/**
 * Big Number Library
 * Developed by JangHyuck Choi & JaeHui In
 * 2020-11-13
 * */
#include "bignum_mul.c"

int main()
{
	srand((unsigned)time(NULL));
	
	bigint* teemo = NULL;

	printf("\n\n\n#create big int\n");
	bi_new(&teemo, 3);
	printf("#created\n\n");

	printf("#set by array\n");
	bi_set_by_array(&teemo, teemo->sign, arr, teemo->wordlen);
	printf("#set completed\n\n");

	printf("#show big int\n");
	printf("#show by base 2: ");
	bi_show(teemo, 2);
	printf("\n");
	// printf("show by base 10: \n");   // ADD, MUL 구현 이후 제작할 예정
	// bi_show(teemo, 10);
	printf("#show by base 16: ");
	bi_show(teemo, 16);
	printf("\n\n");

	// printf("bi_refine: \n");

	printf("# Assign big int x <-- y \n");
	printf("y = 0x");
	bi_show(teemo, 16);
	printf("\n");
	bigint* teemo2 = NULL;
	bi_assign(&teemo2, teemo);
	printf("x = 0x");
	bi_show(teemo2, 16);
	printf("\n");
	printf("print(x == y)");
	printf("\n\n");

	printf("# get word length: ");
	int wordlen = get_wordlen(teemo);
	printf("%d", wordlen);
	printf("\n");

	printf("# get bit length: ");
	int bitlen = get_bitlen(teemo);
	printf("%d\n", bitlen);
	printf("\n");

	printf("# generate random bigint\n# random bigint : ");
	bigint* teemo3 = NULL;
	bi_gen_rand(&teemo3, NON_NEGATIVE, 4); // wordlen 3인 양수의 랜덤 big int 생성
	bi_show(teemo3, 16);
	printf("\n\n");

	printf("# get j-th bit \n");
	// printf("enter j: ");
	int j_th = 4;
	// scanf("%d\n", j);
	int j = get_jth_bit(teemo, j_th);
	// j가 비트 길이를 넘어서면 에러 메세지를 출력해야 함 --> 구현 필요
	printf("# %d-th bit: %d\n\n", j_th, j);

	printf("# get sign and flip sign of big int\n");
	printf("# sign of big int: %d\n", bi_get_sign(teemo));
	bi_flip_sign(&teemo);
	printf("# flipped sign: %d\n\n", bi_get_sign(teemo));

	printf("# big int set one, is one\n");
	bigint* teemo4 = NULL;
	bi_assign(&teemo4, teemo);
	printf("# before set one: ");
	bi_show(teemo4, 16);
	printf("\n");
	printf("# is big int one: %d\n", is_one(teemo4));
	printf("# after set one: ");
	bi_set_one(&teemo4);
	bi_show(teemo4, 16);
	printf("\n");
	printf("# is big int one: %d\n\n", is_one(teemo4));

	printf("# big int set zero, is zero\n");
	bigint* teemo5 = NULL;
	bi_assign(&teemo5, teemo4);
	printf("# before set zero: ");
	bi_show(teemo5, 16);
	printf("\n");
	printf("# is big int zero: %d\n", is_zero(teemo5));
	printf("# after set zero: ");
	bi_set_zero(&teemo5);
	bi_show(teemo5, 16);
	printf("\n");
	printf("# is big int zero: %d\n\n", is_zero(teemo5));

	printf("# compare big int\n");
	printf("x = 0x");
	bi_show(teemo4, 16);
	printf("\n");
	printf("y = 0x");
	bi_show(teemo5, 16);
	printf("\n");
	printf("if x > y:\n\ta = 1\n");
	printf("print(a == %d)\n\n", Compare_AB(&teemo4, &teemo5));

	printf("# left shift\n");
	printf("x = 0x");
	bi_show(teemo4, 16);
	printf("\n");
	printf("y = 0x");
	int shift = 23;
	Left_Shift(&teemo4, shift);
	bi_show(teemo4, 16);
	printf("\n");
	printf("shift = %d\n", shift);
	printf("print(x << shift == y )");
	printf("\n\n");

	printf("# right shift\nx = 0x");
	bi_show(teemo3, 16);
	printf("\n");
	printf("y = 0x");
	Right_Shift(&teemo3, shift);
	bi_show(teemo3, 16);
	printf("\n");
	printf("shift = %d\n", shift);
	printf("print(x >> shift == y )");
	printf("\n\n");


	printf("# big int reduction\nx = 0x");
	Left_Shift(&teemo3, 4);
	bi_show(teemo3, 16);
	printf("\n");
	printf("y = 0x");
	int reduction = 15;
	Reduction(&teemo3, reduction);
	bi_show(teemo3, 16);
	printf("\n");
	printf("reduction = %d\n", reduction);
	printf("print(x%%2**reduction == y )");
	printf("\n\n");
	
	for (int i = 0; i < 50; i++)
	{
		bigint* r0 = NULL;
		bigint* r1 = NULL;
		bigint* r2 = NULL;
		bigint* r3 = NULL;
		bigint* r4 = NULL;
		bigint* r5 = NULL;
		bigint* r6 = NULL;
		bigint* r7 = NULL;
		bigint* r8 = NULL;
		bigint* r9 = NULL;
		bigint* t0 = NULL;
		bigint* t1 = NULL;
		bigint* t2 = NULL;
		bigint* t3 = NULL;
		bigint* t4 = NULL;
		bigint* t5 = NULL;
		bigint* t6 = NULL;
		bigint* t7 = NULL;
		bigint* t8 = NULL;
		bigint* t9 = NULL;
		int random[10] = { 0, };
		int sign[10] = { 0, };
		for (int i = 0; i < 10; i++)
		{
			int r = 3;
			int s = 0;

			while (1)
			{
				r = rand() % 6;
				s = rand() % 2;
				if (r >= 5)
					break;
			}

			random[i] = r;
			sign[i] = s;
		}
		bi_gen_rand(&r0, sign[0], random[0]);
		bi_gen_rand(&r1, sign[1], random[1]);
		bi_gen_rand(&r2, sign[2], random[2]);
		bi_gen_rand(&r3, sign[3], random[3]);
		bi_gen_rand(&r4, sign[4], random[4]);
		bi_gen_rand(&r5, sign[5], random[5]);
		bi_gen_rand(&r6, sign[6], random[6]);
		bi_gen_rand(&r7, sign[7], random[7]);
		bi_gen_rand(&r8, sign[8], random[8]);
		bi_gen_rand(&r9, sign[9], random[9]);
		
		printf("# bigint add \n");
		printf("print(\"add test\")\n");
		int test_num = 0;

		printf("# add test %d\n", test_num);
		printf("x = 0x");
		bi_show(r0, 16);
		printf("\n");
		printf("y = 0x");
		bi_show(r1, 16);
		printf("\n");
		bi_add(r0, r1, &t0);
		printf("print(x + y == 0x");
		bi_show(t0, 16);
		printf(")\n\n");
		test_num += 1;

		printf("# add test %d\n", test_num);
		printf("x = 0x");
		bi_show(r1, 16);
		printf("\n");
		printf("y = 0x");
		bi_show(r2, 16);
		printf("\n");
		bi_add(r1, r2, &t1);
		printf("print(x + y == 0x");
		bi_show(t1, 16);
		printf(")\n\n");
		test_num += 1;

		printf("# add test %d\n", test_num);
		printf("x = 0x");
		bi_show(r2, 16);
		printf("\n");
		printf("y = 0x");
		bi_show(r3, 16);
		printf("\n");
		bi_add(r2, r3, &t2);
		printf("print(x + y == 0x");
		bi_show(t2, 16);
		printf(")\n\n");
		test_num = 0;


		///// add test end

		printf("# big int sub\n");
		printf("print(\"sub test\")\n");

		printf("# sub test %d\n", test_num);
		printf("x = 0x");
		bi_show(r3, 16);
		printf("\n");
		printf("y = 0x");
		bi_show(r4, 16);
		printf("\n");
		bi_add(r3, r4, &t3);
		printf("print(x + y == 0x");
		bi_show(t3, 16);
		printf(")\n\n");
		test_num += 1;

		printf("# sub test %d\n", test_num);
		printf("x = 0x");
		bi_show(r4, 16);
		printf("\n");
		printf("y = 0x");
		bi_show(r5, 16);
		printf("\n");
		bi_add(r4, r5, &t4);
		printf("print(x + y == 0x");
		bi_show(t4, 16);
		printf(")\n\n");
		test_num += 1;

		printf("# sub test %d\n", test_num);
		printf("x = 0x");
		bi_show(r5, 16);
		printf("\n");
		printf("y = 0x");
		bi_show(r6, 16);
		printf("\n");
		bi_add(r5, r6, &t5);
		printf("print(x + y == 0x");
		bi_show(t5, 16);
		printf(")\n\n");
		test_num += 1;

		///// sub test end

		printf("# mul test\n");
		printf("# single pricision test\n");
		printf("print(\"single pricision mul test\")\n");
		bi_mulc(arr[0], arr[1], &t6);
		printf("a = 0x%x\n", arr[0]);
		printf("b = 0x%x\n", arr[1]);
		printf("print(a * b == 0x");
		bi_show(t6, 16);
		printf(")\n\n");

		printf("# multi pricision test (Schoolbook)\n");
		printf("print(\"multi pricison schoolbook mul test\")\n");
		bi_mul(r6, r7, &t7);
		printf("x = 0x");
		bi_show(r6, 16);
		printf("\n");
		printf("y = 0x");
		bi_show(r7, 16);
		printf("\n");
		printf("print(x * y == 0x");
		bi_show(t7, 16);
		printf(")\n\n");
		
		printf("# multi pricision test (Kartusba)\n");

		printf("print(\"multi pricison Karatsuba mul test\")\n");
		bi_kmul(r7, r8, &t8);
		printf("x = 0x");
		bi_show(r7, 16);
		printf("\n");
		printf("y = 0x");
		bi_show(r8, 16);
		printf("\n");
		printf("print(x * y == 0x");
		bi_show(t8, 16);
		printf(")\n\n");


		bi_kmul(r8, r9, &t9);
		printf("x = 0x");
		bi_show(r8, 16);
		printf("\n");
		printf("y = 0x");
		bi_show(r9, 16);
		printf("\n");
		printf("print(x * y == 0x");
		bi_show(t9, 16);
		printf(")\n\n");
	}

	bi_delete(&teemo);
	bi_delete(&teemo2);
	bi_delete(&teemo3);
	bi_delete(&teemo4);
	bi_delete(&teemo5);
	bi_delete(&r0);
	bi_delete(&r1);
	bi_delete(&r2);
	bi_delete(&r3);
	bi_delete(&r4);
	bi_delete(&r5);
	bi_delete(&r6);
	bi_delete(&r7);
	bi_delete(&r8);
	bi_delete(&r9);
	bi_delete(&t0);
	bi_delete(&t1);
	bi_delete(&t2);
	bi_delete(&t3);
	bi_delete(&t4);
	bi_delete(&t5);
	bi_delete(&t6);
	bi_delete(&t7);
	bi_delete(&t8);
	bi_delete(&t9);
	

	return 0;
}