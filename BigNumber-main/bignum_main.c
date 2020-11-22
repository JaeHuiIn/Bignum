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
		printf("press 6 for exit\n");
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
			break;
		default:
			printf("you choose wrong number.\n");
			break;
		}
		

		if(cases == 6) 
			break;
		
	}
	
	/*
	bigint* A = NULL;
	bigint* B = NULL;
	bigint* C = NULL;
	bigint* R = NULL;
	bigint* Q = NULL;

	word arr1[3] = { 0x12345678, 0x000cdef, 0x000cdef };
	word b[2] = { 0x9f4265a8, 0x9a53b531 };
	word c[2] = { 0x53256, 0x9a53b531 };
	bi_new(&A, 3);
	bi_set_by_array(&A, 0, arr1, 3);
	bi_new(&B, 2);
	bi_set_by_array(&B, 0, b, 2);
	bi_new(&C, 2);
	bi_set_by_array(&C, 0, c, 2);
	bi_divc(A, B, &Q, &R);
	printf("\na = 0x");
	bi_show(A, 16);
	printf("\nb = 0x");
	bi_show(B, 16);
	printf("\nq = 0x", Q);
	bi_show(Q, 16);
	printf("\nr = 0x", Q);
	bi_show(R, 16);
	printf("\nprint(r == a- (b*q))\n");
	
	bi_divc(A, C, &Q, &R);
	printf("\na = 0x");
	bi_show(A, 16);
	printf("\nb = 0x");
	bi_show(C, 16);
	printf("\nq = 0x", Q);
	bi_show(Q, 16);
	printf("\nr = 0x", Q);
	bi_show(R, 16);
	printf("\nprint(r == a- (b*q))\n");
	*/
	printf("Thanks for using!\n");
	return 0;
}