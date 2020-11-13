#include "bignum_add_sub.c"

void bi_mulc(word x, word y, bigint** C)
{
   //이거 word로 한거 다 bigint로 생성해서 마지막에 delete를 해야하나? 
	word crr = 0;
   word R_x = x >> (WORD_BITLEN / 2);      // x를 절반으로 나눈 앞 자리
   word L_x = x % (1 << (WORD_BITLEN / 2));// x를 절반으로 나눈 뒷 자리
   word R_y = y >> (WORD_BITLEN / 2);      // y를 절반으로 나눈 앞 자리
   word L_y = y % (1 << (WORD_BITLEN/2));  // y를 절반으로 나눈 뒷 자리
   word A0, A1, AA, AA0, AA1;  //계산한 것을 저장할 곳
   word c = 0;
   A1 = R_x * R_y; // 앞 자리끼리 곱
   A0 = L_x * L_y; // 뒷 자리끼리 곱
   AA = ((R_x * L_y) + (L_x * R_y)); // 대각선 곱의 합
   if (AA < (R_x * L_y))
   {
	   crr = 1;
   }
   AA1 = AA >> (WORD_BITLEN / 2); // 대각선 곱의 앞자리
   AA0 = AA << (WORD_BITLEN / 2); // 대각선 곱의 뒷자리
   AA1 += crr << (WORD_BITLEN / 2);
   // 뒷자리에서 carry 발생
   if (A0 > A0 + AA0)
      c = 1;

   if (A1 + AA1 + c == 0)
   {
      bi_new(C, 1);
      (*C)->a[0] = A0 + AA0;
   }
   else
   {
      bi_new(C, 2);
      (*C)->a[1] = A1 + AA1 + c;
      (*C)->a[0] = A0 + AA0;
   }
}

void bi_mul(bigint* x, bigint* y, bigint** C)
{
	bigint* C_word = NULL;  // singhle pricision을 저장하는 bigint 구조체
	bigint* Copy_C = NULL;
	bigint* add_C = NULL;

	int max_len = x->wordlen + y->wordlen;  //C의 최대 길이

	bi_new(&Copy_C, max_len);   // 곱셈 결과를 저장할 C를 max_len 길이로 초기화
	bi_new(&add_C, max_len);
	for (int i = 0; i < x->wordlen; i++)
	{
		for (int j = 0; j < y->wordlen; j++)
		{
			bi_new(&C_word, 2);     // 2개의 워드를 저장할 수 있는 공간 할당.
			bi_mulc(x->a[i], y->a[j], &C_word);          // 한 워드씩 곱
			Left_Shift(&C_word, WORD_BITLEN * (i + j));  // 제대로 된 위치로 설정
			bi_add(C_word, add_C, &Copy_C);
			bi_assign(&add_C, Copy_C);
		}
	}

	if (x->sign == y->sign)         //부호 맞추기
		Copy_C->sign = NON_NEGATIVE;
	else
		Copy_C->sign = NEGATIVE;
	bi_refine(Copy_C);
	bi_assign(C, Copy_C);

	bi_delete(&add_C);
	bi_delete(&C_word);
	bi_delete(&Copy_C);
}

void bi_kmul(bigint* x, bigint* y, bigint** C)
{
	int flag = 2;
	if (flag >= x->wordlen || flag >= y->wordlen)
	{
		bi_mul(x, y, C);
		return;
	}

	int l;
	if(x->wordlen > y->wordlen)
		l = (x->wordlen + 1) >> 1;
	else
		l = (y->wordlen + 1) >> 1;
	bigint* A0 = NULL;
	bigint* A1 = NULL;
	bigint* B0 = NULL;
	bigint* B1 = NULL;
	// bi_new(&A0, l); bi_new(&A1, l); bi_new(&B0, l); bi_new(&B1, l);
	bi_assign(&A0, x);
	bi_assign(&A1, x);
	bi_assign(&B0, y);
	bi_assign(&B1, y);

	Right_Shift(&A1, WORD_BITLEN * l);
	Reduction(&A0, WORD_BITLEN * l);
	Right_Shift(&B1, WORD_BITLEN * l);
	Reduction(&B0, WORD_BITLEN * l);

	bigint* T1 = NULL;
	bigint* T0 = NULL;
	bigint* Copy_T1 = NULL;
	bi_new(&T1, 2 * l);
	bi_new(&T0, 2 * l);
	bi_kmul(A1, B1, &T1);
	bi_kmul(A0, B0, &T0);

	bigint* R = NULL;
	bi_new(&R, 4 * l);
	bi_assign(&Copy_T1, T1);
	Left_Shift(&T1, 2 * l * WORD_BITLEN);
	bi_add(T1, T0, &R);


	bigint* S1 = NULL;
	bigint* S0 = NULL;
	bi_new(&S1, 2 * l);
	bi_new(&S0, 2 * l);
	bi_sub(A0, A1, &S1);
	bi_sub(B1, B0, &S0);

	bigint* S = NULL;
	bigint* Copy_S = NULL;
	bi_new(&S, 2 * l);
	int S_sign = S1->sign ^ S0->sign;
	if (S1->sign == NEGATIVE)
		bi_flip_sign(&S1);
	if (S0->sign == NEGATIVE)
		bi_flip_sign(&S1);
	bi_kmul(S1, S0, &S);
	S->sign = S_sign;      // 이게 맞는 표현??


	bi_assign(&Copy_S, S);
	if (S->sign == Copy_T1->sign)
	{
		bi_add(S, Copy_T1, &Copy_S);
		Copy_S->sign = S->sign;
	}
	else
	{
		if (S->sign = NEGATIVE)
		{
			if (Compare_ABS(S, Copy_T1) == 1)
			{
				bi_flip_sign(&S);
				bi_sub(Copy_T1, S, &Copy_S);
			}
			else if (Compare_ABS(S, Copy_T1) == 0)
			{
				bi_set_zero(&Copy_S);
			}
			else
			{
				bi_flip_sign(&S);
				bi_sub(Copy_T1, S, &Copy_S);
			}
		}
		else
		{
			if (Compare_ABS(S, Copy_T1) == 1)
			{
				bi_flip_sign(&T1);
				bi_sub(S, Copy_T1, &Copy_S);
			}
			else if (Compare_ABS(S, Copy_T1) == 0)
			{
				bi_set_zero(&Copy_S);
			}
			else
			{
				bi_flip_sign(&Copy_T1);
				bi_sub(S, Copy_T1, &Copy_S);
			}
		}
	}
	if (Copy_S->sign == T0->sign)
	{
		bi_add(Copy_S, T0, &S);
		S->sign = Copy_S->sign;
	}
	else
	{
		if (Copy_S->sign = NEGATIVE)
		{
			if (Compare_ABS(Copy_S, T0) == 1)
			{
				bi_flip_sign(&Copy_S);
				bi_sub(T0, Copy_S, &S);
			}
			else if (Compare_ABS(Copy_S, T0) == 0)
			{
				bi_set_zero(&S);
			}
			else
			{
				bi_flip_sign(&Copy_S);
				bi_sub(T0, Copy_S, &S);
			}
		}
		else
		{
			if (Compare_ABS(Copy_S, T0) == 1)
			{
				bi_flip_sign(&T0);
				bi_sub(Copy_S, T0, &S);
			}
			else if (Compare_ABS(Copy_S, T0) == 0)
			{
				bi_set_zero(&S);
			}
			else
			{
				bi_flip_sign(&T0);
				bi_sub(Copy_S, T0, &S);
			}
		}
	}

	Left_Shift(&S, WORD_BITLEN * l);
	bigint* Copy_R = NULL;
	bi_assign(&Copy_R, R);


	bi_add(Copy_R, S, &R);
	bi_refine(R);
	bi_assign(C, R);  // 맞는 표현?

	bi_delete(&A0);
	bi_delete(&A1);
	bi_delete(&B0);
	bi_delete(&B1);
	bi_delete(&T0);
	bi_delete(&T1);
	bi_delete(&R);
	bi_delete(&S0);
	bi_delete(&S1);
	bi_delete(&S);
	bi_delete(&Copy_S);
	bi_delete(&Copy_R);
	// pesudo code 같이 구현은 완료....
}