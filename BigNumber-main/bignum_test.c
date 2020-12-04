#include "bignum_all_header.h"

void bignumber_test()
{
	while(1) {
		system("cls");
		int choose;
		printf("Choose your work\n");
		printf("Press 1 to check speed\n");
		printf("Press 2 to check accuracy\n");
		printf("Press 3 to calculate\n");
		printf("Press 4 to EXIT\n");
		printf("Press: ");
		scanf("%d", &choose);
		printf("\n\n");	

		if(choose == 1) {	// check time
			speed_check();
		}
		else if(choose == 2) {	// check accuracy
			accuracy_check();

		}
		else if(choose == 3) {
			calculate_bignumber();
		}
		else if(choose == 4)
			break;
		else 
			printf("You choose wrong number\n");
	
	}

}


void speed_check()
{
	while(1) {
		system("cls");
		int select;
		printf("Select a function to check speed\n");
		printf("1. ADD\n2. SUB\n3. schoolbook MUL\n");
        printf("4. karatsuba MUL\n5. schoolbook SQUARING\n6. karatsuba SQUARING\n");
        printf("7. binary-long-division\n8. multi-precision-division\n9. EXIT\n");
		printf("Select: ");
		scanf("%d", &select);
		switch (select) {
			case 1:
				add_speed();
				break;
			case 2:
				sub_speed();
				break;	
			case 3:
				schoolbook_mul_speed();
				break;
			case 4:
				karatsuba_mul_speed();
				break;
			case 5:
				Schoolbook_Squaring_speed();
				break;
			case 6:
                Karatsuba_Squaring_speed();
				break;
            case 7:
                Binary_Long_Division_speed();
                break;
            case 8:
                Multiprecision_Division_speed();
                break;
            case 9: 
                break;
			default:
				printf("You choose wrong number\n");
				break;
	
		}
		if(select == 9)
				break;
	}

}

void accuracy_check()
{
	while(1){
		system("cls");
		int select;
		printf("You can check accuracy by SAGE\n");
		printf("Select function to check accuracy\n");
		printf("1. basic function\n2. ADD\n3. SUB\n4. MUL\n5. DIV\n6. MOD_EXP\n7. EXIT\n");
		printf("Select: ");
		scanf("%d", &select);

		switch (select) {
			case 1:
				basic_test();
				break;
			case 2:
				add_test();
				break;
			case 3:
				sub_test();
				break;	
			case 4:
				mul_test();
				break;
			case 5:
				div_test();
				break;
			case 6:
				mod_exp_test();
				break;
			case 7:
				break;
			default:
				printf("You choose wrong number\n");
				system("pause");
				break;
		
			
		}
		if(select == 7)
			break;

	}

}

void calculate_bignumber()
{
	while(1) {
		system("cls");
		int select;
		printf("Select a function to execute\n");
		printf("1. ADD\n2. SUB\n3. MUL\n4. DIV\n5. MOD_EXP\n6. EXIT\n");
		printf("Select: ");
		scanf("%d", &select);
		switch (select) {
			case 1:
				calculate_add();
				break;
			case 2:
				calculate_sub();
				break;	
			case 3:
				calculate_mul();
				break;
			case 4:
				calculate_div();
				break;
			case 5:
				calculate_mod_exp();
				break;
			case 6:
				break;
			default:
				printf("You choose wrong number\n");
				break;
	
		}
		if(select == 6)
			break;
	}

}


void add_speed()
{
    int check;  // 테스트 데이터 쌍 개수
    int first_number_wordlen;   // 첫번째 bigint의 워드길이
    int second_number_wordlen;  // 두번째 bigint의 워드길이

	system("cls");
    printf("Enter number for checks(1 for basic setting): ");
    scanf("%d", &check);
	if(check == 1) {
		check = 10000;
		first_number_wordlen = 100;
		second_number_wordlen = 40;
	}
	else {
	    printf("Enter number for first number's wordlen: ");
    	scanf("%d", &first_number_wordlen);
    	printf("Enter number for second number's wordlen: ");
    	scanf("%d", &second_number_wordlen);
	}

    bigint* A = NULL;
    bigint* B = NULL;
    bigint* C = NULL;
    bi_gen_rand(&A, 0, first_number_wordlen);
    bi_gen_rand(&B, 0, second_number_wordlen);

    clock_t start, end; // 시간 측정용 변수

    start = clock();    // 측정 시작
    for(int i = 0; i < check / 3; i++){
        bi_add(A, B, &C);   
        bi_add(C, A, &B);
        bi_add(B, C, &A);
    }
    end = clock();      // 측정 종료

    printf("Add function Time: %lf\n", (double)(end - start) / CLOCKS_PER_SEC);
	system("pause");

    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&C);
}

void sub_speed()
{
	system("cls");
    int check;  // 테스트 데이터 쌍 개수
    int first_number_wordlen;   // 첫번째 bigint의 워드길이
    int second_number_wordlen;  // 두번째 bigint의 워드길이

    printf("Enter number for checks(1 for basic setting): ");
    scanf("%d", &check);
    if(check == 1) {
		check = 10000;
		first_number_wordlen = 100;
		second_number_wordlen = 40;
	}
	else {
	    printf("Enter number for first number's wordlen: ");
    	scanf("%d", &first_number_wordlen);
    	printf("Enter number for second number's wordlen: ");
    	scanf("%d", &second_number_wordlen);
	}

    bigint* A = NULL;
    bigint* B = NULL;
    bigint* C = NULL;
    bi_gen_rand(&A, 0, first_number_wordlen);
    bi_gen_rand(&B, 0, second_number_wordlen);

    clock_t start, end; // 시간 측정용 변수

    start = clock();    // 측정 시작
    for(int i = 0; i < check / 3; i++) {
        bi_sub(A, B, &C);   
        bi_sub(C, A, &B);
        bi_sub(B, C, &A);
    }
    end = clock();

    printf("Sub function Time: %lf\n", (double)(end - start) / CLOCKS_PER_SEC);
	system("pause");

    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&C);
    
}

void schoolbook_mul_speed()
{
	system("cls");
    int check;  // 테스트 데이터 쌍 개수
    int first_number_wordlen;   // 첫번째 bigint의 워드길이
    int second_number_wordlen;  // 두번째 bigint의 워드길이

    printf("Enter number for checks(1 for basic setting): ");
    scanf("%d", &check);
    if(check == 1) {
		check = 1000;
		first_number_wordlen = 100;
		second_number_wordlen = 40;
	}
	else {
	    printf("Enter number for first number's wordlen: ");
    	scanf("%d", &first_number_wordlen);
    	printf("Enter number for second number's wordlen: ");
    	scanf("%d", &second_number_wordlen);
	}

    bigint* A = NULL;
    bigint* B = NULL;
    bigint* C = NULL;
    bi_gen_rand(&A, 0, first_number_wordlen);
    bi_gen_rand(&B, 0, second_number_wordlen);

    clock_t start, end; // 시간 측정용 변수

    start = clock();    // 측정 시작
	// int checks[4] = {0, };
    for(int i = 0; i < check; i++) {
		/*
		if(check / (i + 1) >= 90 && checks[0] == 0){
			system("cls");
			printf("%d%%", 10);
			checks[0] = 1;
		}
		else if(check / (i + 1) >= 70 && checks[1] == 0){
			system("cls");
			printf("%d%%", 30);
			checks[1] = 1;			
		}
		else if(check / (i + 1) >= 50 && checks[2] == 0){
			system("cls");
			printf("%d%%", 50);
			checks[2] = 1;
		}
		else if(check / (i + 1) >= 10 && checks[3] == 0){
			system("cls");
			printf("%d%%", 90);
			checks[3] = 1;
		}*/

        bi_mul(A, B, &C);
    }
    end = clock();

	system("cls");
    printf("Schoolbook multiplication Time: %lf\n", (double)(end - start) / CLOCKS_PER_SEC);
	system("pause");

    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&C);
}

void karatsuba_mul_speed()
{
	system("cls");
    int check;  // 테스트 데이터 쌍 개수
    int first_number_wordlen;   // 첫번째 bigint의 워드길이
    int second_number_wordlen;  // 두번째 bigint의 워드길이

    printf("Enter number for checks(1 for basic setting): ");
    scanf("%d", &check);
    if(check == 1) {
		check = 1000;
		first_number_wordlen = 100;
		second_number_wordlen = 40;
	}
	else {
	    printf("Enter number for first number's wordlen: ");
    	scanf("%d", &first_number_wordlen);
    	printf("Enter number for second number's wordlen: ");
    	scanf("%d", &second_number_wordlen);
	}

    bigint* A = NULL;
    bigint* B = NULL;
    bigint* C = NULL;
    bi_gen_rand(&A, 0, first_number_wordlen);
    bi_gen_rand(&B, 0, second_number_wordlen);

    clock_t start, end; // 시간 측정용 변수

    start = clock();    // 측정 시작
	
    for(int i = 0; i < check; i++) {
		

        bi_kmulc(A, B, &C);
    }
    end = clock();

    printf("Karatsuba multiplication Time: %lf\n", (double)(end - start) / CLOCKS_PER_SEC);
	system("pause");

    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&C);
}

void Schoolbook_Squaring_speed()
{
	system("cls");
    int check;  // 테스트 데이터 쌍 개수
    int first_number_wordlen;   // 첫번째 bigint의 워드길이

    printf("Enter number for checks(1 for basic setting): ");
    scanf("%d", &check);
    if(check == 1) {
		check = 1000;
		first_number_wordlen = 100;
	}
	else {
	    printf("Enter number for first number's wordlen: ");
    	scanf("%d", &first_number_wordlen);
	}

    bigint* A = NULL;
    bigint* B = NULL;
    bi_gen_rand(&A, 0, first_number_wordlen);

    clock_t start, end; // 시간 측정용 변수

    start = clock();
    for(int i = 0; i < check; i++){
        bi_squaring(A, &B);
    }
    end = clock();

    printf("Schoolbook Squaring Time: %lf\n", (double)(end - start) / CLOCKS_PER_SEC);
	system("pause");

    bi_delete(&A);
    bi_delete(&B);    

}

void Karatsuba_Squaring_speed()
{
	system("cls");
    int check;  // 테스트 데이터 쌍 개수
    int first_number_wordlen;   // 첫번째 bigint의 워드길이

    printf("Enter number for checks(1 for basic setting): ");
    scanf("%d", &check);
    if(check == 1) {
		check = 1000;
		first_number_wordlen = 100;
	}
	else {
	    printf("Enter number for first number's wordlen: ");
    	scanf("%d", &first_number_wordlen);
	}

    bigint* A = NULL;
    bigint* B = NULL;
    bi_gen_rand(&A, 0, first_number_wordlen);

    clock_t start, end; // 시간 측정용 변수

    start = clock();
    for(int i = 0; i < check; i++){
        bi_ksquaringC(A, &B);
    }
    end = clock();

    printf("Karatsuba Squaring Time: %lf\n", (double)(end - start) / CLOCKS_PER_SEC);
	system("pause");

    bi_delete(&A);
    bi_delete(&B);
}

void Binary_Long_Division_speed()
{
	system("cls");	
    int check;  // 테스트 데이터 쌍 개수
    int first_number_wordlen;   // 첫번째 bigint의 워드길이
    int second_number_wordlen;  // 두번째 bigint의 워드길이

    printf("Enter number for checks(1 for basic setting): ");
    scanf("%d", &check);
    if(check == 1) {
		check = 1000;
		first_number_wordlen = 100;
		second_number_wordlen = 40;
	}
	else {
	    printf("Enter number for first number's wordlen: ");
    	scanf("%d", &first_number_wordlen);
    	printf("Enter number for second number's wordlen: ");
    	scanf("%d", &second_number_wordlen);
	}

    bigint* A = NULL;
    bigint* B = NULL;
    bigint* Q = NULL;
    bigint* R = NULL;
    bi_gen_rand(&A, 0, first_number_wordlen);
    bi_gen_rand(&B, 0, second_number_wordlen);

    clock_t start, end; // 시간 측정용 변수

    start = clock();    // 측정 시작
    for(int i = 0; i < check; i++) {
        Binary_Long_Division(A, B, &Q, &R);
    }
    end = clock();

    printf("Binary Lond Division Time: %lf\n", (double)(end - start) / CLOCKS_PER_SEC);
	system("pause");

    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&Q);
    bi_delete(&R);

}

void Multiprecision_Division_speed()
{
	system("cls");
    int check;  // 테스트 데이터 쌍 개수
    int first_number_wordlen;   // 첫번째 bigint의 워드길이
    int second_number_wordlen;  // 두번째 bigint의 워드길이

    printf("Enter number for checks(1 for basic setting): ");
    scanf("%d", &check);
    if(check == 1) {
		check = 1000;
		first_number_wordlen = 100;
		second_number_wordlen = 40;
	}
	else {
	    printf("Enter number for first number's wordlen: ");
    	scanf("%d", &first_number_wordlen);
    	printf("Enter number for second number's wordlen: ");
    	scanf("%d", &second_number_wordlen);
	}

    bigint* A = NULL;
    bigint* B = NULL;
    bigint* Q = NULL;
    bigint* R = NULL;
    bi_gen_rand(&A, 0, first_number_wordlen);
    bi_gen_rand(&B, 0, second_number_wordlen);

    clock_t start, end; // 시간 측정용 변수

    start = clock();    // 측정 시작
    for(int i = 0; i < check; i++) {
        DIV(A, B, &Q, &R);
    }
    end = clock();

    printf("Multi-precision Division Time: %lf\n", (double)(end - start) / CLOCKS_PER_SEC);
	system("pause");

    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&Q);
    bi_delete(&R);

}


void basic_test()
{
	system("cls");
	bigint* teemo1 = NULL;
	bigint* teemo2 = NULL;
	bigint* teemo3 = NULL;
	bigint* teemo4 = NULL;

	// Create bigint
	printf("\n#create big int\n");
	bi_new(&teemo1, 3);
	printf("created\n\n");

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

	system("pause");

	bi_delete(&teemo1);
	bi_delete(&teemo2);
	bi_delete(&teemo3);
	bi_delete(&teemo4);
}

void add_test()
{
	system("cls");
	int check, upper_limit, lower_limit;
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


	int random[1000] = { 0, };
	int sign[1000] = { 0, };

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

	system("pause");

}

void sub_test()
{
	system("cls");
	int check, upper_limit, lower_limit;
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


	int random[1000] = { 0, };
	int sign[1000] = { 0, };

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

	system("pause");

}

void mul_test()
{
	system("cls");
	int check, upper_limit, lower_limit;
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

	int random[1000] = { 0, };
	int sign[1000] = { 0, };

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


	bi_delete(&a0);
	bi_delete(&a1);
	bi_delete(&t0);

	system("pause");

}

void div_test()
{
	system("cls");
	int check, upper_limit, lower_limit;
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


	int random[1000] = { 0, };

	// create integer for random wordlen. sign is always POSITIVE
	for (int i = 0; i < check + 1; i++) {
		while (1) {
			random[i] = rand() % upper_limit;
			if (random[i] >= lower_limit)
				break;
		}
	}

	int choose;
	printf("Choose your work\n1. School book Binary Long Division \n2. Multi-Pricision Long Division\n");
	scanf("%d", &choose);
	bigint* A = NULL;
	bigint* B = NULL;
	bigint* Q = NULL;
	bigint* R = NULL;


	if (choose == 1) {
		int ran1;
		int ran2;


		printf("# SAGE code\n");
		for (int i = 0; i < check; i++) {
			while (1) {
				ran1 = rand() % check;
				ran2 = (ran1 + 1) % check;

				bi_gen_rand(&A, 0, random[ran1]);
				bi_gen_rand(&B, 0, random[ran2]);

				if (Compare_ABS(A, B) >= 0)
					break;
			}

			printf("x = 0x");
			bi_show(A, 16);
			printf("\n");
			printf("y = 0x");
			bi_show(B, 16);
			printf("\n");

			Binary_Long_Division(A, B, &Q, &R);

			printf("Q = 0x");
			bi_show(Q, 16);
			printf("\n");
			printf("R = 0x");
			bi_show(R, 16);
			printf("\n");

			printf("print((x %% y == R) and (x // y) == Q)\n\n");
		}


	}
	else if (choose == 2) {
		// test for multi-pricision Division
		int ran1;
		int ran2;
		printf("# SAGE code\n");
		for(int i = 0; i < check; i++) {
			while (1) {
				ran1 = rand() % check;
				ran2 = (ran1 + 1) % check;

				bi_gen_rand(&A, 0, random[ran1]);
				bi_gen_rand(&B, 0, random[ran2]);

				if (Compare_ABS(A, B) >= 0)
					break;
			}
			printf("x = 0x");
			bi_show(A, 16);
			printf("\n");
			printf("y = 0x");
			bi_show(B, 16);
			printf("\n");
			DIV(A, B, &Q, &R);
			printf("Q = 0x");
			bi_show(Q, 16);
			printf("\n");
			printf("R = 0x");
			bi_show(R, 16);
			printf("\n");

			printf("print((x %% y == R) and ((x // y) == Q))\n\n");

		}


	}
	else
		printf("You choose wrong number\n");
	
	
	bi_delete(&A);
	bi_delete(&B);
	bi_delete(&Q);
	bi_delete(&R);

	system("pause");

}

void mod_exp_test()
{
	system("cls");
	int check, upper_limit, lower_limit, n, N;
	printf("enter number for check(press 1 for basic setting): ");
	scanf("%d", &check);
	if (check == 1) {
		check = 50;
		upper_limit = 50;
		lower_limit = 30;
		n = 2;
		N = 10;
	}
	else {
		printf("enter upper limit: ");
		scanf("%d", &upper_limit);
		printf("enter lower limit: ");
		scanf("%d", &lower_limit);
		printf("enter exponential number's wordlen: ");
		scanf("%d", &n);
		printf("enter N's wordlen: ");
		scanf("%d", &N);
		printf("\n");
	}

	int random[1000] = {0, };

	// create integer for random wordlen. sign is always POSITIVE
	for (int i = 0; i < check + 1; i++) {
		while (1) {
			random[i] = rand() % upper_limit;
			if (random[i] >= lower_limit)
				break;
		}
	}

	int choose;
	printf("Choose your work\n1. Left-to-Right\n2. Right-to-Left\n3. Multiply-and-Squaring\n");
	scanf("%d", &choose);
	bigint* A = NULL;
	bigint* nn = NULL;
	bigint* NN = NULL;


	if(choose == 1) {
		// Left-to-Right
		printf("# SAGE code\n");
		for (int i = 0; i < check; i++) {
			do
			{
				bi_gen_rand(&A, 0, random[i]);
				bi_gen_rand(&NN, 0, N);
				bi_gen_rand(&nn, 0, n);
			}while (is_zero(A) == 0 || is_zero(NN) == 0 || is_zero(nn) == 0);
			printf("x = 0x");
			bi_show(A, 16);
			printf("\n");

			printf("n = 0x");
			bi_show(nn, 16);
			printf("\n");

			printf("N = 0x");
			bi_show(NN, 16);
			printf("\n");

			ModExp_LTR(&A, nn, NN);

			printf("z = 0x");
			bi_show(A, 16);
			printf("\n");

			printf("print(power_mod(x, n, N) == z)\n\n");
		}

	}
	else if(choose == 2) {
		// Right-to-Left
		printf("# SAGE code\n");
		for(int i = 0; i < check; i++) {
			do
			{
				bi_gen_rand(&A, 0, random[i]);
				bi_gen_rand(&NN, 0, N);
				bi_gen_rand(&nn, 0, n);
			} while (is_zero(A) == 0 || is_zero(NN) == 0 || is_zero(nn) == 0);

			printf("x = 0x");
			bi_show(A, 16);
			printf("\n");

			printf("n = 0x");
			bi_show(nn, 16);
			printf("\n");

			printf("N = 0x");
			bi_show(NN, 16);
			printf("\n");

			ModExp_RTL(&A, nn, NN);

			printf("z = 0x");
			bi_show(A, 16);
			printf("\n");

			printf("print(power_mod(x, n, N) == z)\n\n");
		}

	}
	else if(choose == 3) {
		// Multiply-and-Squaring
		printf("# SAGE code\n");
		for(int i = 0; i < check; i++) {
			do
			{
				bi_gen_rand(&A, 0, random[i]);
				bi_gen_rand(&NN, 0, N);
				bi_gen_rand(&nn, 0, n);
			} while (is_zero(A) == 0 || is_zero(NN) == 0 || is_zero(nn) == 0);

			printf("x = 0x");
			bi_show(A, 16);
			printf("\n");


			printf("n = 0x");
			bi_show(nn, 16);
			printf("\n");

			printf("N = 0x");
			bi_show(NN, 16);
			printf("\n");

			ModExp_Montgomery(&A, nn, NN);

			printf("z = 0x");
			bi_show(A, 16);
			printf("\n");

			printf("print(power_mod(x, n, N) == z)\n\n");
		}


	}
	else
		printf("You choose wrong number\n");

	bi_delete(&A);
	bi_delete(&NN);
	bi_delete(&nn);

	system("pause");


}


void calculate_add()
{
	int base;
	int num, A_sign, B_sign;
	int sign1, sign2;
	char* str1 = malloc(sizeof(char) * 2048);
	char* str2 = malloc(sizeof(char) * 2048);
	bigint* A = NULL;
	bigint* B = NULL;
	bigint* C = NULL;
	system("cls");
	printf("Choose string base size\n");
	printf("1. Base 2\n2. Base 10\n3. Base 16\nEnter Base: ");
	scanf("%d", &base);
	num = base;
	/*
	첫번째 빅넘버 문자열 입력 구현 필요

	char str1[] = "1234";	// <-- 임의로 구현한것. 동적 할당으로 새로 구현 필요함
	*/
	printf("set sign of A and B\nSign of A: ");
	scanf("%d", &sign1);
	A_sign = sign1;
	printf("Enter frist big number by string: ");
	scanf("%s", str1);
	bi_set_by_string(&A, A_sign, str1, num);
	printf("Sign of B: ");
	scanf("%d", &sign2);
	B_sign = sign2;
	printf("Enter second big number by string: ");
	/*
	두번째 빅넘버 문자열 입력 구현 필요
	
	char str2[] = "1234";	// <-- 임의로 구현한것. 동적 할당으로 새로 구현 필요함
	*/
	scanf("%s", str2);
	bi_set_by_string(&B, B_sign, str2, num);

	if(num == 2)
		printf("result: 0b");
	else if (num == 10)
		printf("result: ");
	else if (num == 16)
		printf("result: 0x");

	bi_add(A, B, &C);
	bi_show(C, num);
	printf("\n");

	bi_delete(&A);
	bi_delete(&B);
	bi_delete(&C);
	free(str1);
	free(str2);
	system("pause");
}

void calculate_sub()
{
	int base;
	int num, A_sign, B_sign;
	int sign1, sign2;
	char* str1 = malloc(sizeof(char) * 2048);
	char* str2 = malloc(sizeof(char) * 2048);
	bigint* A = NULL;
	bigint* B = NULL;
	bigint* C = NULL;
	system("cls");
	printf("Choose string base size\n");
	printf("1. Base 2\n2. Base 10\n3. Base 16\nEnter Base: ");
	scanf("%d", &base);
	num = base;
	/*
	첫번째 빅넘버 문자열 입력 구현 필요

	char str1[] = "1234";	// <-- 임의로 구현한것. 동적 할당으로 새로 구현 필요함
	*/
	printf("set sign of A and B\nSign of A: ");
	scanf("%d", &sign1);
	A_sign = sign1;
	printf("Enter frist big number by string: ");
	scanf("%s", &str1);
	bi_set_by_string(&A, A_sign, str1, num);
	printf("Sign of B: ");
	scanf("%d", sign2);
	B_sign = sign2;
	printf("Enter second big number by string: ");
	/*
	두번째 빅넘버 문자열 입력 구현 필요

	char str2[] = "1234";	// <-- 임의로 구현한것. 동적 할당으로 새로 구현 필요함
	*/
	scanf("%s", str2);
	bi_set_by_string(&B, B_sign, str2, num);

	if (num == 2)
		printf("result: 0b");
	else if (num == 10)
		printf("result: ");
	else if (num == 16)
		printf("result: 0x");

	bi_sub(A, B, &C);
	bi_show(C, num);
	printf("\n");

	bi_delete(&A);
	bi_delete(&B);
	bi_delete(&C);
	free(str1);
	free(str2);
	system("pause");
}

void calculate_mul()
{
	int base;
	int num, A_sign, B_sign;

	system("cls");
	printf("Choose string base size\n");
	printf("1. Base 2\n2. Base 10\n3. Base 16\nEnter Base: ");
	scanf("%d", &base);
	num = base;

	printf("Press 1 for Karatsuba Multiplication\n");
	printf("Press 2 for karatsuba Squaring\nEnter: ");
	int press;
	scanf("%d", &press);

	if (press == 1) {
		bigint* A = NULL;
		bigint* B = NULL;
		bigint* C = NULL;

		char* str1 = malloc(sizeof(char) * 2048);
		char* str2 = malloc(sizeof(char) * 2048);
		int sign1, sign2;

		printf("set sign of A and B\nSign of A: ");
		scanf("%d", &sign1);
		A_sign = sign1;
		printf("Enter frist big number by string: ");
		scanf("%s", str1);

		bi_set_by_string(&A, A_sign, str1, num);
		printf("Sign of B: ");
		scanf("%d", &sign2);
		B_sign = sign2;
		printf("Enter second big number by string: ");

		scanf("%s", str2);
		bi_set_by_string(&B, B_sign, str2, num);

		bi_show(A, num);
		printf("\n");
		bi_show(B, num);
		printf("\n");
		if (num == 2)
			printf("result: 0b");
		else if (num == 10)
			printf("result: ");
		else if (num == 16)
			printf("result: 0x");

		bi_mul(A, B, &C);
		bi_show(C, num);
		printf("\n");

		bi_delete(&A);
		bi_delete(&B);
		bi_delete(&C);
		free(str1);
		free(str2);


	}
	else if (press == 2) {
		char* str1 = malloc(sizeof(char) * 2048);
		int sign1;
		bigint* A = NULL;
		bigint* B = NULL;

		printf("set sign of A\nSign of A: ");
		scanf("%d", &sign1);
		A_sign = sign1;
		printf("Enter frist big number by string: ");
		scanf("%s", str1);
		bi_set_by_string(&A, A_sign, str1, num);
		if (num == 2)
			printf("result: 0b");
		else if (num == 10)
			printf("result: ");
		else if (num == 16)
			printf("result: 0x");

		bi_ksquaringC(A, &B);
		bi_show(B, base);
		printf("\n");
		bi_delete(&A);
		bi_delete(&B);
		free(str1);
	}

	system("pause");

}

void calculate_div()
{
	int base;
	int num, A_sign, B_sign;
	int sign1, sign2;
	char* str1 = malloc(sizeof(char) * 2048);
	char* str2 = malloc(sizeof(char) * 2048);
	bigint* A = NULL;
	bigint* B = NULL;
	bigint* Q = NULL;
	bigint* R = NULL;
	system("cls");
	printf("Choose string base size\n");
	printf("1. Base 2\n2. Base 10\n3. Base 16\nEnter Base: ");
	scanf("%d", &base);
	num = base;
	/*
	첫번째 빅넘버 문자열 입력 구현 필요

	char str1[] = "1234";   // <-- 임의로 구현한것. 동적 할당으로 새로 구현 필요함
	*/
	printf("set sign of A and B\nSign of A: ");
	scanf("%d", &sign1);
	A_sign = sign1;
	printf("Enter frist big number by string: ");
	scanf("%s", str1);
	bi_set_by_string(&A, A_sign, str1, num);
	printf("Sign of B: ");
	scanf("%d", &sign2);
	B_sign = sign2;
	printf("Enter second big number by string: ");
	/*
	두번째 빅넘버 문자열 입력 구현 필요

	char str2[] = "1234";   // <-- 임의로 구현한것. 동적 할당으로 새로 구현 필요함
	*/
	scanf("%s", str2);
	bi_set_by_string(&B, B_sign, str2, num);

	DIV(A, B, &Q, &R);
	printf("result: \n");
	if (num == 2)
	{
		printf("Q: 0b");
		bi_show(Q, num);
		printf("\nR: 0b");
		bi_show(R, num);
		printf("\n");

	}
	else if (num == 10)
	{
		printf("Q: ");
		bi_show(Q, num);
		printf("\nR: ");
		bi_show(R, num);
		printf("\n");

	}
	else if (num == 16)
	{
		printf("Q: 0x");
		bi_show(Q, num);
		printf("\nR: 0x");
		bi_show(R, num);
		printf("\n");

	}


	bi_delete(&A);
	bi_delete(&B);
	bi_delete(&Q);
	bi_delete(&R);
	free(str1);
	free(str2);
	system("pause");

}

void calculate_mod_exp()
{
	int base;
	int choose;
	int num, A_sign, B_sign, C_sign;
	int sign1, sign2, sign3;
	char* str1 = malloc(sizeof(char) * 2048);
	char* str2 = malloc(sizeof(char) * 2048);
	char* str3 = malloc(sizeof(char) * 2048);
	bigint* A = NULL;
	bigint* B = NULL;
	bigint* C = NULL;
	system("cls");
	printf("Choose string base size\n");
	printf("1. Base 2\n2. Base 10\n3. Base 16\nEnter Base: ");
	scanf("%d", &base);
	num = base;

	printf("set sign of A and B and C\nSign of A: ");
	scanf("%d", &sign1);
	A_sign = sign1;
	printf("Enter frist big number by string: ");
	scanf("%s", str1);
	bi_set_by_string(&A, A_sign, str1, num);
	
	printf("Sign of B: ");
	scanf("%d", &sign2);
	B_sign = sign2;
	printf("Enter second big number by string: ");
	scanf("%s", str2);
	bi_set_by_string(&B, B_sign, str2, num);

	printf("Sign of C: ");
	scanf("%d", &sign3);
	C_sign = sign3;
	printf("Enter second big number by string: ");
	scanf("%s", str3);
	bi_set_by_string(&C, C_sign, str3, num);

	printf("Choose your style\n");
	printf("1. Left to Right\n2. Right to Left\n3. Montgomery\nchoose: ");
	scanf("%d", &choose);

	if(choose == 1)
		ModExp_LTR(&A, B, C);
	else if(choose == 2)
		ModExp_RTL(&A, B, C);
	else if(choose == 3)
		ModExp_Montgomery(&A, B, C);

	if (num == 2)
		printf("result: 0b");
	else if (num == 10)
		printf("result: ");
	else if (num == 16)
		printf("result: 0x");
	bi_show(A, num);
	printf("\n");

	bi_delete(&A);
	bi_delete(&B);
	bi_delete(&C);
	free(str1);
	free(str2);
	free(str3);

	system("pause");
	
}





