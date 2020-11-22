#include "bignum_test.h"

void basic_test()
{
	bigint* teemo1 = NULL;
	bigint* teemo2 = NULL;
	bigint* teemo3 = NULL;
	bigint* teemo4 = NULL;

	// Create bigint
	printf("\n#create big int\n");
	bi_new(&teemo1, 3);
	printf("created\n\n");

	// set bigint by array
	printf("set by array\n");
	bi_set_by_array(&teemo1, teemo1->sign, arr, teemo1->wordlen);
	printf("set completed\n\n");

	// show big int
	printf("#show big int\n");
	printf("#show by base 2: ");
	bi_show(teemo1, 2);
	printf("\n");
	// printf("show by base 10: \n");
   // bi_show(teemo, 10);
	printf("#show by base 16: ");
	bi_show(teemo1, 16);
	printf("\n\n");
	/*
	NEED TO IMPLEMENT BASE 10
	*/

	// assign bigint (only test for x > 0)
	printf("# Assign big int x <-- y \n");
	printf("y = 0x");
	bi_show(teemo1, 16);
	printf("\n");
	bi_assign(&teemo2, teemo1);
	printf("x = 0x");
	bi_show(teemo2, 16);
	printf("\n");
	printf("print(x == y)");
	printf("\n\n");

	// get word bitlen of bigint
	printf("# get word length: ");
	int wordlen = get_wordlen(teemo1);
	printf("%d\n\n", wordlen);

	// get bit length 
	printf("# get bit length: ");
	int bitlen = get_bitlen(teemo1);
	printf("%d\n\n", bitlen);

	// generate random bigint
	printf("# random bigint : ");
	bi_gen_rand(&teemo3, NON_NEGATIVE, 4);
	bi_show(teemo3, 16);
	printf("\n\n");

	// get j-bit of bigint
	int j = 4;
	// printf("# enter j: ");
	// scanf("%d\n", j);
	int j_th = get_jth_bit(teemo1, j);
	printf("# %d-th bit: %d\n\n", j, j_th);

	// flip sign of bigint
	printf("# get sign and flip sign of big int\n");
	printf("# sign of big int: %d\n", bi_get_sign(teemo1));
	bi_flip_sign(&teemo1);
	printf("# flipped sign: %d\n\n", bi_get_sign(teemo1));

	// set one, is one
	bi_assign(&teemo4, teemo1);
	printf("# before set one: ");
	bi_show(teemo4, 16);
	printf("\n");
	printf("# is bigint one: %d\n", is_one(teemo4));
	printf("# after set one: ");
	bi_set_one(&teemo4);
	bi_show(teemo4, 16);
	printf("\n");
	printf("# is big int one: %d\n\n", is_one(teemo4));

	// set zero, is zero
	printf("# before set zero: ");
	bi_show(teemo4, 16);
	printf("\n");
	printf("# is big int zero: %d\n", is_zero(teemo4));
	printf("# after set zero: ");
	bi_set_zero(&teemo4);
	bi_show(teemo4, 16);
	printf("\n");
	printf("# is big int zero: %d\n\n", is_zero(teemo4));

	// compare bigint
	bi_gen_rand(&teemo3, 0, 5);
	bi_gen_rand(&teemo4, 0, 5);
	printf("x = 0x");
	bi_show(teemo3, 16);
	printf("\n");
	printf("y = 0x");
	bi_show(teemo4, 16);
	printf("\n");
	int compare = Compare_AB(&teemo3, &teemo4);
	printf("if x > y --> 1\nif x == y --> 0\nif x < y --> -1\n");
	printf("result = %d\n\n", compare);

	// left shift of bigint
	int shift = 24;
	printf("# left shift\n");
	printf("x = 0x");
	bi_show(teemo3, 16);
	printf("\n");
	printf("y = 0x");
	Left_Shift(&teemo3, shift);
	bi_show(teemo3, 16);
	printf("\n");
	printf("# SAGE code\n");
	printf("shift = %d\n", shift);
	printf("print(x << shift == y )\n\n");

	// right shift of bigint
	shift = 24;
	printf("# right shift\n");
	printf("x = 0x");
	bi_show(teemo3, 16);
	printf("\n");
	printf("y = 0x");
	Right_Shift(&teemo3, shift);
	bi_show(teemo3, 16);
	printf("\n");
	printf("# SAGE code\n");
	printf("shift = %d\n", shift);
	printf("print(x >> shift == y )");
	printf("\n\n");

	// big int reduction
	int reduction = 15;
	printf("# big int reduction\n");
	printf("x = 0x");
	bi_show(teemo3, 16);
	printf("\n");
	printf("y = 0x");
	Reduction(&teemo3, reduction);
	bi_show(teemo3, 16);
	printf("\n");
	printf("# SAGE code\n");
	printf("reduction = %d\n", reduction);
	printf("print(x%%2**reduction == y)\n\n");

	bi_delete(&teemo1);
	bi_delete(&teemo2);
	bi_delete(&teemo3);
	bi_delete(&teemo4);
}

void add_test()
{
	int check = 10;
	int upper_limit = 15;
	int lower_limit = 5;
	printf("enter number for check(press 1 for basic setting): ");
	scanf("%d", &check);
	if (check == 1) {
		check = 50;
		upper_limit = 50;
		lower_limit = 30;
	}
	else {
		printf("enter upper limit: ");
		scanf("%d", &upper_limit);
		printf("enter lower limit: ");
		scanf("%d", &lower_limit);
		printf("\n");
	}


	int random[100] = { 0, };
	int sign[100] = { 0, };

	// create integer for random wordlen and sign
	for (int i = 0; i < check + 1; i++) {
		while (1) {
			random[i] = rand() % upper_limit;
			sign[i] = rand() % 2;
			if (random[i] >= lower_limit)
				break;
		}

	}

	// test for bigint addition
	printf("# SAGE code\n");
	for (int i = 0; i < check; i++) {
		printf("# Add test %d\n", i);

		bigint* a0 = NULL;
		bigint* a1 = NULL;
		bigint* t0 = NULL;

		bi_gen_rand(&a0, sign[i], random[i]);
		bi_gen_rand(&a1, sign[i + 1], random[i + 1]);

		if (a0->sign == NON_NEGATIVE) {
			printf("x = 0x");
			bi_show(a0, 16);
			printf("\n");
		}
		else {
			bi_flip_sign(&a0);
			printf("x = -0x");
			bi_show(a0, 16);
			printf("\n");
			bi_flip_sign(&a0);
		}

		if (a1->sign == NON_NEGATIVE) {
			printf("y = 0x");
			bi_show(a1, 16);
			printf("\n");
		}
		else {
			bi_flip_sign(&a1);
			printf("y = -0x");
			bi_show(a1, 16);
			printf("\n");
			bi_flip_sign(&a1);
		}

		bi_add(a0, a1, &t0);
		if (t0->sign == NON_NEGATIVE) {
			printf("z = 0x");
			bi_show(t0, 16);
			printf("\n");
		}
		else {
			bi_flip_sign(&t0);
			printf("z = -0x");
			bi_show(t0, 16);
			printf("\n");
			bi_flip_sign(&t0);
		}

		printf("print(x + y == z)\n\n");

		bi_delete(&a0);
		bi_delete(&a1);
		bi_delete(&t0);

	}

}

void sub_test()
{
	int check = 10;
	int upper_limit = 15;
	int lower_limit = 5;
	printf("enter number for check(press 1 for basic setting): ");
	scanf("%d", &check);
	if (check == 1) {
		check = 50;
		upper_limit = 50;
		lower_limit = 30;
	}
	else {
		printf("enter upper limit: ");
		scanf("%d", &upper_limit);
		printf("enter lower limit: ");
		scanf("%d", &lower_limit);
		printf("\n");
	}


	int random[100] = { 0, };
	int sign[100] = { 0, };

	// create integer for random wordlen and sign
	for (int i = 0; i < check + 1; i++) {
		while (1) {
			random[i] = rand() % upper_limit;
			sign[i] = rand() % 2;
			if (random[i] >= lower_limit)
				break;
		}

	}

	// test for bigint subtraction
	printf("# SAGE code\n");
	for (int i = 0; i < check; i++) {
		printf("# Sub test %d\n", i);

		bigint* a0 = NULL;
		bigint* a1 = NULL;
		bigint* t0 = NULL;

		bi_gen_rand(&a0, sign[i], random[i]);
		bi_gen_rand(&a1, sign[i + 1], random[i + 1]);

		if (a0->sign == NON_NEGATIVE) {
			printf("x = 0x");
			bi_show(a0, 16);
			printf("\n");
		}
		else {
			bi_flip_sign(&a0);
			printf("x = -0x");
			bi_show(a0, 16);
			printf("\n");
			bi_flip_sign(&a0);
		}

		if (a1->sign == NON_NEGATIVE) {
			printf("y = 0x");
			bi_show(a1, 16);
			printf("\n");
		}
		else {
			bi_flip_sign(&a1);
			printf("y = -0x");
			bi_show(a1, 16);
			printf("\n");
			bi_flip_sign(&a1);
		}

		bi_sub(a0, a1, &t0);
		if (t0->sign == NON_NEGATIVE) {
			printf("z = 0x");
			bi_show(t0, 16);
			printf("\n");
		}
		else {
			bi_flip_sign(&t0);
			printf("z = -0x");
			bi_show(t0, 16);
			printf("\n");
			bi_flip_sign(&t0);
		}

		printf("print(x - y == z)\n\n");

		bi_delete(&a0);
		bi_delete(&a1);
		bi_delete(&t0);

	}

}

void mul_test()
{
	int check = 10;
	int upper_limit = 15;
	int lower_limit = 5;
	printf("enter number for check(press 1 for basic setting): ");
	scanf("%d", &check);
	if (check == 1) {
		check = 50;
		upper_limit = 50;
		lower_limit = 30;
	}
	else {
		printf("enter upper limit: ");
		scanf("%d", &upper_limit);
		printf("enter lower limit: ");
		scanf("%d", &lower_limit);
		printf("\n");
	}

	int random[100] = { 0, };
	int sign[100] = { 0, };

	// create integer for random wordlen and sign
	for (int i = 0; i < check + 1; i++) {
		while (1) {
			random[i] = rand() % upper_limit;
			sign[i] = rand() % 2;
			if (random[i] >= lower_limit)
				break;
		}

	}

	int choose;
	printf("Choose your work\n1. School book multiplication \n2. Squaring \n3. Karatsuba Multiplication\n4. Karatsuba Squaring \n");
	scanf("%d", &choose);

	bigint* a0 = NULL;
	bigint* a1 = NULL;
	bigint* t0 = NULL;
	clock_t start = clock();
	if (choose == 1) {
		// test for School book multiplication
		printf("# SAGE code\n");
		for (int i = 0; i < check; i++) {
			printf("# Mul test (School Book) %d\n", i);

			bi_gen_rand(&a0, sign[i], random[i]);
			bi_gen_rand(&a1, sign[i + 1], random[i + 1]);

			if (a0->sign == NON_NEGATIVE) {
				printf("x = 0x");
				bi_show(a0, 16);
				printf("\n");
			}
			else {
				bi_flip_sign(&a0);
				printf("x = -0x");
				bi_show(a0, 16);
				printf("\n");
				bi_flip_sign(&a0);
			}

			if (a1->sign == NON_NEGATIVE) {
				printf("y = 0x");
				bi_show(a1, 16);
				printf("\n");
			}
			else {
				bi_flip_sign(&a1);
				printf("y = -0x");
				bi_show(a1, 16);
				printf("\n");
				bi_flip_sign(&a1);
			}

			bi_mul(a0, a1, &t0);
			if (t0->sign == NON_NEGATIVE) {
				printf("z = 0x");
				bi_show(t0, 16);
				printf("\n");
			}
			else {
				bi_flip_sign(&t0);
				printf("z = -0x");
				bi_show(t0, 16);
				printf("\n");
				bi_flip_sign(&t0);
			}

			printf("print(x * y == z)\n\n");


		}
		printf("\n\n");
	}
	else if (choose == 2) {
		// test for Squaring
		printf("# SAGE code\n");
		for (int i = 0; i < check; i++) {
			printf("# Squaring test (Squaring) %d\n", i);

			bi_gen_rand(&a0, sign[i], random[i]);

			if (a0->sign == NON_NEGATIVE) {
				printf("x = 0x");
				bi_show(a0, 16);
				printf("\n");
			}
			else {
				bi_flip_sign(&a0);
				printf("x = -0x");
				bi_show(a0, 16);
				printf("\n");
				bi_flip_sign(&a0);
			}

			bi_squaring(a0, &t0);
			printf("z = 0x");
			bi_show(t0, 16);
			printf("\n");

			printf("print(x**2 == z)\n\n");

		}
		printf("\n\n");
	}
	else if (choose == 3) {
		// test for Karatsuba multiplication
		printf("# SAGE code\n");
		for (int i = 0; i < check; i++) {
			printf("# Mul test (Karatsuba) %d\n", i);

			bi_gen_rand(&a0, sign[i], random[i]);
			bi_gen_rand(&a1, sign[i + 1], random[i + 1]);

			if (a0->sign == NON_NEGATIVE) {
				printf("x = 0x");
				bi_show(a0, 16);
				printf("\n");
			}
			else {
				bi_flip_sign(&a0);
				printf("x = -0x");
				bi_show(a0, 16);
				printf("\n");
				bi_flip_sign(&a0);
			}

			if (a1->sign == NON_NEGATIVE) {
				printf("y = 0x");
				bi_show(a1, 16);
				printf("\n");
			}
			else {
				bi_flip_sign(&a1);
				printf("y = -0x");
				bi_show(a1, 16);
				printf("\n");
				bi_flip_sign(&a1);
			}

			bi_kmulc(a0, a1, &t0);
			if (t0->sign == NON_NEGATIVE) {
				printf("z = 0x");
				bi_show(t0, 16);
				printf("\n");
			}
			else {
				bi_flip_sign(&t0);
				printf("z = -0x");
				bi_show(t0, 16);
				printf("\n");
				bi_flip_sign(&t0);
			}

			printf("print(x * y == z)\n\n");
		}
		printf("\n\n");
	}
	else if (choose == 4) {
	// test for Karatsuba Squaring
	printf("# SAGE code\n");
	for (int i = 0; i < check; i++) {
		printf("# Squaring test (Karatsuba Squaring) %d\n", i);

		bi_gen_rand(&a0, sign[i], random[i]);

		if (a0->sign == NON_NEGATIVE) {
			printf("x = 0x");
			bi_show(a0, 16);
			printf("\n");
		}
		else {
			bi_flip_sign(&a0);
			printf("x = -0x");
			bi_show(a0, 16);
			printf("\n");
			bi_flip_sign(&a0);
		}
		bi_ksquaringC(a0, &t0);
		printf("z = 0x");
		bi_show(t0, 16);
		printf("\n");

		printf("print(x**2 == z)\n\n");

	}
	printf("\n\n");
	}
	else
		printf("you choose wrong number\n");

	clock_t end = clock();
	printf("Time : %lf\n", (double)(end - start) / CLOCKS_PER_SEC);

	bi_delete(&a0);
	bi_delete(&a1);
	bi_delete(&t0);

}

void div_test()
{
	int check = 10;
	int upper_limit = 15;
	int lower_limit = 5;
	printf("enter number for check(press 1 for basic setting): ");
	scanf("%d", &check);
	if (check == 1) {
		check = 50;
		upper_limit = 50;
		lower_limit = 30;
	}
	else {
		printf("enter upper limit: ");
		scanf("%d", &upper_limit);
		printf("enter lower limit: ");
		scanf("%d", &lower_limit);
		printf("\n");
	}


	int random[100] = { 0, };

	// create integer for random wordlen and sign
	for (int i = 0; i < check + 1; i++) {
		while (1) {
			random[i] = rand() % upper_limit;
			if (random[i] >= lower_limit)
				break;
		}

	}

	// test for bigint division
	printf("# SAGE code\n");
	for (int i = 0; i < check; i++) {
		bigint* a0 = NULL;
		bigint* a1 = NULL;
		bigint* Q = NULL;
		bigint* R = NULL;

		while (1) {
			bi_gen_rand(&a0, 0, random[i]);
			bi_gen_rand(&a1, 0, random[i + 1]);
			if (Compare_ABS(a0, a1) >= 0)
				break;
		}

		printf("x = 0x");
		bi_show(a0, 16);
		printf("\n");
		printf("y = 0x");
		bi_show(a1, 16);
		printf("\n");

		DIV(a0, a1, &Q, &R);

		printf("Q = 0x");
		bi_show(Q, 16);
		printf("\n");
		printf("R = 0x");
		bi_show(R, 16);
		printf("\n");

		printf("print((x % y == R) & (x // y) == Q)\n\n");

		bi_delete(&a0);
		bi_delete(&a1);
		bi_delete(&Q);
		bi_delete(&R);

	}
}
