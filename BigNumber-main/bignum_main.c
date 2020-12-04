#include "bignum_all_header.h"

int main()
{
	
	srand((unsigned)time(NULL));
	
	bignumber_test();

	system("cls");
	
	printf("Thanks for using!\n");
	system("pause");
	system("cls");
	
	/*
	bigint* T1 = NULL;
	bigint* T2 = NULL;
	bigint* T3 = NULL;

	word arr1[1] = { 10 };
	word arr2[2] = { 5 };
	bi_new(&T1, 1);
	bi_new(&T2, 1);

	bi_set_by_array(&T1, NON_NEGATIVE, arr1, 1);
	bi_set_by_array(&T2, NON_NEGATIVE, arr2, 1);

	printf("\n");
	bi_show(T1, 10);
	printf("\n");
	bi_show(T2, 10);

	bi_kmulc(T1, T2, &T3);
	printf("\n");
	bi_show(T3, 10);
	bi_ksquaringC(T1, &T3);
	printf("\n");
	bi_show(T3, 10);


	
	char a[1];
	scanf("%s", &a);
	int base = 16;
	bigint* Teemo = NULL;

	bi_set_by_string(&Teemo, NON_NEGATIVE, a, 10);


	bi_show(Teemo, base);
	printf("\n");


	bi_show(Teemo, base);
	printf("\n");

	bi_delete(&Teemo);
	
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
	bigint* A = NULL;
	bigint* B = NULL;
	bigint* C = NULL;
	char str1[1], str2[1];
	int sign1, sign2;

	printf("set sign of A and B\nSign of A: ");
	scanf("%d", &sign1);
	A_sign = sign1;
	printf("Enter frist big number by string: ");
	scanf("%s", &str1);

	bi_set_by_string(&A, A_sign, str1, num);
	printf("Sign of B: ");
	scanf("%d", &sign2);
	B_sign = sign2;
	printf("Enter second big number by string: ");

	scanf("%s", &str2);
	bi_set_by_string(&B, B_sign, str2, num);

	if (num == 2)
		printf("result: 0b");
	else if (num == 10)
		printf("result: ");
	else if (num == 16)
		printf("result: 0x");

	printf("\n A = ");
	bi_show(A, num);
	printf("\n B = ");
	bi_show(B, num);

	bi_kmulc(A, B, &C);
	bi_show(C, num);
	printf("\n");

	bi_delete(&A);
	bi_delete(&B);
	bi_delete(&C);*/
	return 0;
}


/*
	char a[] = "3456789876543456";

	bigint* Teemo = NULL;

	bi_set_by_string(&Teemo, NON_NEGATIVE, a, 10);


	
	bi_show(Teemo, 16);
	printf("\n");


	bi_show(Teemo, 16);
	printf("\n");

	bi_delete(&Teemo);
	*/