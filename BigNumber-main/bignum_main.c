#include "bignum_all_header.h"

int main()
{
	/*
	srand((unsigned)time(NULL));
	
	bignumber_test();

	system("cls");
	
	printf("Thanks for using!\n");
	system("pause");
	system("cls");
	*/


	char a[1];
	scanf("%s", &a);
	
	bigint* Teemo = NULL;

	bi_set_by_string(&Teemo, NON_NEGATIVE, a, 10);



	bi_show(Teemo, 16);
	printf("\n");


	bi_show(Teemo, 16);
	printf("\n");

	bi_delete(&Teemo);

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