#include "bignum_all_header.h"

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
		printf("PRESS: ");
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
	for(int i = 0; i < 10; i++){
		printf("sc%d\n", i);
		Binary_Long_Division_speed();
		printf("ka%d\n", i);
		Multiprecision_Division_speed();
	}
	*/


	printf("Thanks for using!\n");
	

	return 0;
}