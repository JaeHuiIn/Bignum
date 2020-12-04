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
	
	char* a = malloc(sizeof(char) * 2048);
	scanf("%s", a);
	
	bigint* Teemo = NULL;
	bi_set_by_string(&Teemo, NON_NEGATIVE, a, 10);

	bi_show(Teemo, 10);
	printf("\n");
	bi_show(Teemo, 16);
	printf("\n");

	bi_delete(&Teemo);
	free(a);
	/*
	61316549116464a6464b6546465413d6546f546c3213e454
	*/

	return 0;
}