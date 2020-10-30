/**
 * Big Number Library
 * Developed by JangHyuck Choi & JaeHui In
 * 2020-10-11
 * */
#include "1011big_num_header.h"


int main()
{
	// WORD_BITLEN 을 선택하게 하는 과정이 추가되어야 한다.


	word arr[3] = { 0x1234, 0x5678, 0x9abc };
	bigint teemo;
	bigint* teemo_p = &teemo;
	teemo.sign = NON_NEGATIVE;
	teemo.wordlen = 3;
	bigint teemo2;
	bigint* teemo2_p = &teemo2;
	
	bigint teemo3;
	bigint* teemo3_p = &teemo3;
	
	bigint teemo4;
	bigint* teemo4_p = &teemo4;
	/*
	더블 포인터 구조체 참고
	mystruct actualThing;
	mystruct *pointer = &actualThing;
	mystruct **data = &pointer;
	myfunc(data);
	*/
	/*
	printf("create big int\n");
	bi_new(&teemo_p, 3);
	printf("\n");

	printf("set by array\n");
	bi_set_by_array(&teemo_p, teemo.sign, arr, teemo.wordlen);
	printf("\n");
	*/
	printf("bi_show\n");
	printf("show by base 2: \n");
	bi_show(teemo_p, 2);
	// printf("show by base 10: \n");   // ADD, MUL 구현 이후 제작할 예정
	// bi_show(teemo_p, 10);
	printf("show by base 16: \n");
	bi_show(teemo_p, 16);
	printf("\n");

	//  printf("bi_refine: \n");    // 어떻게 보일 것인가?

	printf("Assign big int: A <-- B \n");
	printf("show big int B: \n");
	bi_show(teemo_p, 16);
	bi_assign(&teemo2_p, teemo_p);
	printf("show assigned big int A: \n");
	bi_show(teemo2_p, 16);
	printf("\n");

	printf("generate random bigint:\n");
	bigint teemo3;
	bigint* teemo3_p = &teemo3;
	bi_gen_rand(&teemo3_p, NON_NEGATIVE, 3); // wordlen 3인 양수의 랜덤 big int 생성
	bi_show(teemo3_p, 16);
	printf("\n");

	printf("get word length: ");
	int wordlen = get_wordlen(teemo_p);
	printf("%d", wordlen);
	printf("\n");

	printf("get bit length: ");
	int bitlen = get_bitlen(teemo_p);
	printf("%d", bitlen);
	printf("\n");

	printf("get j-th bit \n");
	printf("enter j: ");
	int j = 3;
	// scanf("%d\n", j);
	j = get_jth_bit(teemo_p, j);
	// j가 비트 길이를 넘어서면 에러 메세지를 출력해야 함 --> 구현 필요
	printf("j-th bit: %d", j);
	printf("\n");

	printf("A.Sign : %d\n", bi_get_sign(teemo_p);
	printf("Change A.sign : %d\n", bi_flip_sign(teemo_p));


	printf("Number is zero? : ");
	printf("%d\n", is_zero(teemo_p));
	printf("Assign big int: A <-- C \n");
	printf("show big int C: ");
	bi_assign(&teemo3_p, teemo_p);




	printf("Change C to zero : ");
	bi_set_zero(teemo3_p);
	bi_show(teemo3_p, 16);
	printf("\n");
	
	printf("Number is one? : \n");
	printf("%d\n", is_one(teemo_p));
	printf("Assign big int: A <-- D \n");
	printf("show big int D: ");
	bi_assign(&teemo4_p, teemo_p);
	printf("Change D to one : ");
	bi_set_one(teemo4_p);
	bi_show(teemo4_p, 16);
	printf("\n");

	






	return 0;

}