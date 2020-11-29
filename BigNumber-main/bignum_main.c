/**
 * Big Number Library
 * Developed by JangHyuck Choi & JaeHui In
 * 2020-11-13
 * */
#include "bignum_test.c"
int main()
{
	
	srand((unsigned)time(NULL));
	
	
	while(1) {			
		int cases = 0;
		printf("press 1 for basic test\n");
		printf("press 2 for big number addition test\n");
		printf("press 3 for big number subtraction test\n");
		printf("press 4 for big number multiplication\n");
		printf("press 5 for big number division test\n");
		printf("press 6 for big number modular exponentiation\n");
		printf("press 7 for exit\n");
		scanf("%d", &cases);
		switch (cases)
		{
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
			printf("you choose wrong number.\n");
			break;
		}
		

		if(cases == 7) 
			break;
		
	}
	
	
	
	/*
	// 에러 검사용 주석
	bigint* A = NULL;
	bigint* B = NULL;
	bigint* C = NULL;
	bigint* R = NULL;
	bigint* Q = NULL;

	word arr1[2] = { 0x9abcdef09abcdef0, 0x58659653a8659653 };//, 0x1234567812345678};
	word b[1] = { 0xa534629815346298 }; //, 0xa8659653a8659653};
	word c[2] = { 0x23a569bd23a569bd, 0x99a5b63299a5b632 };
	bi_new(&A, 2);
	bi_set_by_array(&A, 0, arr1, 2);
	bi_new(&B, 1);
	bi_set_by_array(&B, 0, b, 1);
	bi_new(&C, 2);
	bi_set_by_array(&C, 0, c, 2);
	printf("\na = 0x");
	bi_show(A, 16);
	printf("\nb = 0x");
	bi_show(B, 16);

	L_D_A(A, b[0], &Q);
	bi_divcc(A, B, &Q, &R);
	
	printf("\nq = 0x", Q);
	bi_show(Q, 16);
	printf("\nr = 0x", Q);
	bi_show(R, 16);
	printf("\nprint(q == a//b)\n");
	printf("print(r == a - b*q)\n");

	bi_divcc(A, C, &Q, &R);

	printf("\na = 0x");
	bi_show(A, 16);
	printf("\nb = 0x");
	bi_show(C, 16);
	printf("\nq = 0x", Q);
	bi_show(Q, 16);
	printf("\nr = 0x", Q);
	bi_show(R, 16);
	printf("\nprint(q == a//b)");
	printf("\nprint(r == a - b*q)\n");
	
	*/



	/*	
	char a[] = "3456789876543456";

	bigint* Teemo = NULL;

	bi_set_by_string(&Teemo, NON_NEGATIVE, a, 10);


	
	bi_show(Teemo, 2);
	printf("\n");


	bi_show(Teemo, 16);
	printf("\n");
	*/



	printf("Thanks for using!\n");
	

	return 0;
}