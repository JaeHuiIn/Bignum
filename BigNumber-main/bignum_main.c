#include "bignum_all_header.h"

int main()
{
	
	srand((unsigned)time(NULL));
	
	/*
	char a[] = "3456789876543456";
	
	bigint* Teemo = NULL;
	bi_set_by_string(&Teemo, NON_NEGATIVE, a, 10);
	bi_show(Teemo, 16);
	printf("\n");

	bi_show(Teemo, 10);
	printf("\n");


	bi_delete(&Teemo);

	

	add_speed();
	*/
	
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
	

	printf("Thanks for using!\n");
	

	return 0;
}