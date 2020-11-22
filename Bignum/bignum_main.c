/**
 * Big Number Library
 * Developed by JangHyuck Choi & JaeHui In
 * 2020-11-13
 * */
#include "bignum_test.c"

int main()
{
	srand((unsigned)time(NULL));

	// basic_test();

	// add_test();

	// sub_test();

	mul_test();
	/*
	bigint* t1 = NULL;
	bigint* t2 = NULL;
	bigint* t3 = NULL;

	bi_new(&t1, 2);
	bi_new(&t2, 2);

	word arr1[2] = { 0x77, 0xfd};
	word arr2[2] = { 0xbd, 0xb7 };
	
	bi_set_by_array(&t1, 0, arr1, 2);
	bi_set_by_array(&t2, 0, arr2, 2);
	printf("x = 0x");
	bi_show(t1, 16);
	//printf("\ny = 0x");
	//bi_show(t2, 16);
	bi_squaring(t1, &t3);
	printf("\nz = 0x");
	bi_show(t3, 16);
	printf("\nprint(hex(x*x))\nprint(x*x == z)");
	bi_delete(&t1);
	bi_delete(&t2);
	bi_delete(&t3);
	*/
	return 0;
}