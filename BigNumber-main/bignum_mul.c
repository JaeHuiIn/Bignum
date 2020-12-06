#include "bignum_all_header.h"

void bi_mulc(word x, word y, bigint** C)
{
	word crr = 0;
   	word R_x = x >> (WORD_BITLEN / 2);          // X1 (x를 절반으로 나눈 앞 자리)
   	word L_x = x % (1ULL << (WORD_BITLEN / 2)); // X0 (x를 절반으로 나눈 뒷 자리)
	word R_y = y >> (WORD_BITLEN / 2);          // Y1 (y를 절반으로 나눈 앞 자리)
   	word L_y = y % (1ULL << (WORD_BITLEN/2));   // Y0 (y를 절반으로 나눈 뒷 자리)
	word A0, A1, AA, AA0, AA1, AAA;             
   	word c = 0;
   	A1 = R_x * R_y;                              // X1 * Y1
   	A0 = L_x * L_y;                              // X0 * Y0
   	AA = ((R_x * L_y) + (L_x * R_y));            // AA = X1 * Y0 + X0 * Y1
   	if (AA < (R_x * L_y))
   	{
	  crr = 1;
   	}
   	AA1 = AA >> (WORD_BITLEN / 2);              // AA1 (대각선 곱의 앞자리)
   	AA0 = AA << (WORD_BITLEN / 2);              // AA0 (대각선 곱의 뒷자리)
   	AA1 += crr << (WORD_BITLEN / 2);
   	// 뒷자리에서 carry 발생
	AAA = A0 + AA0;
	if (A0 > AAA)
		c = 1;

	if (A1 + AA1 + c == 0)                       // C->wordlen == 1
   	{
   	   bi_new(C, 1);
       (*C)->a[0] = A0 + AA0;
    }
    else                                         // C->wordlen == 2
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
	bi_set_zero(&Copy_C);
	for (int i = 0; i < x->wordlen; i++)
	{
		for (int j = 0; j < y->wordlen; j++)
		{
			bi_new(&C_word, 2);                          // 2개의 워드를 저장할 수 있는 공간 할당.
			bi_mulc(x->a[i], y->a[j], &C_word);          // C_word = x_i * y_i
			Left_Shift(&C_word, WORD_BITLEN * (i + j));  // 제대로 된 위치로 설정
			bi_add(C_word, add_C, &Copy_C);              // 이 전의 값과 방금 계산한 값 덧셈
			bi_assign(&add_C, Copy_C);
		}
	}
	if (x->sign == y->sign)                              //부호 맞추기
		Copy_C->sign = NON_NEGATIVE;
	else
		Copy_C->sign = NEGATIVE;
	bi_refine(Copy_C);

	bi_assign(C, Copy_C);
	bi_delete(&add_C);
	bi_delete(&C_word);
	bi_delete(&Copy_C);
}

void bi_self_mul(bigint** x, bigint* y)
{
	bigint* Copy_x = NULL;
	bi_assign(&Copy_x, *x);                  // assign "x" to "Copy_x"
	bi_mul(Copy_x, y, x);                    // mul계산
	bi_delete(&Copy_x);
}

void bi_kmul(bigint* x, bigint* y, bigint** C, int flag)
{
	if (flag >= x->wordlen || flag >= y->wordlen)   // if flag >= min(Wordlen(A), Wordlen(B))
	{
		bi_mul(x, y, C);
		return;
	}

	int l;
	if(x->wordlen > y->wordlen)             // l <- (max(Wordlen(A), Wordlen(B))+1) >> 1
		l = (x->wordlen + 1) >> 1;
	else
		l = (y->wordlen + 1) >> 1;
	int lw = l * WORD_BITLEN;

	bigint* A0 = NULL;
	bigint* A1 = NULL;
	bigint* B0 = NULL;
	bigint* B1 = NULL;
	bi_assign(&A0, x);           
	bi_assign(&A1, x);
	bi_assign(&B0, y);
	bi_assign(&B1, y);

	Right_Shift(&A1, lw);      // A1 = x >> lw
	Reduction(&A0, lw);        // A0 = x mod 2^lw
	Right_Shift(&B1, lw);      // B1 = y >> lw
	Reduction(&B0, lw);        // B0 = y mod 2^lw

	bigint* T1 = NULL;
	bigint* T0 = NULL;
	bi_new(&T1, 2 * l);
	bi_new(&T0, 2 * l);
	bi_kmul(A1, B1, &T1, flag);    // T1 = kmul(A1, B1)
	bi_kmul(A0, B0, &T0, flag);    // T0 = kmul(A0, B0)

	bigint* R = NULL;
	bigint* Copy_T1 = NULL;
	bi_new(&R, 4 * l);
	bi_assign(&Copy_T1, T1);
	Left_Shift(&Copy_T1, 2 * lw);
	bi_add(Copy_T1, T0, &R);       // R <- (T1 << 2lw) + T0

	bigint* S1 = NULL;
	bigint* S0 = NULL;
	bi_new(&S1, 2 * l);
	bi_new(&S0, 2 * l);
	bi_sub(A0, A1, &S1);          // S1 = sub(A0, A1) 
	bi_sub(B1, B0, &S0);          // S0 = sub(B1, B0) 

	bigint* S = NULL;
	bi_new(&S, 2 * l);
	int S_sign = S1->sign ^ S0->sign;
	if (S1->sign == NEGATIVE)
		bi_flip_sign(&S1);
	if (S0->sign == NEGATIVE)
		bi_flip_sign(&S0);

	bi_kmul(S1, S0, &S, flag);    // S <- kmul(|S1|, |S0|)
	S->sign = S_sign;


	bigint* Copy_S = NULL;
	bigint* Copy_SS = NULL;	
	bi_assign(&Copy_S, S);
	bi_add(Copy_S, T1, &S);      // S <- add(S, T1)
	bi_assign(&Copy_SS, S);
	bi_add(Copy_SS, T0, &S);     // S <- add(S, T0)
	Left_Shift(&S, lw);          // S <- S << lw 

	bigint* Copy_R = NULL;
	bi_assign(&Copy_R, R);
	bi_add(Copy_R, S, &R);       // R <- add(R, S)
	bi_refine(R);
	bi_assign(C, R); 

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
	bi_delete(&Copy_T1);
	bi_delete(&Copy_S);
	bi_delete(&Copy_SS);
	bi_delete(&Copy_R);
}

void bi_kmulc(bigint* x, bigint* y, bigint** C)
{
	int sign = 0;
	bigint* TEMP = NULL;

	if(x->sign != y->sign)              // 부호 정하기
		sign = NEGATIVE;
	else
		sign = NON_NEGATIVE;
	
	x->sign = NON_NEGATIVE;
	y->sign = NON_NEGATIVE;

	int flag = x->wordlen;              //  flag 설정
	if(flag > y->wordlen)
		flag = y->wordlen;

	flag = flag / 2;
	if (flag == 0)                       //  if flag == 0 -> mul
	{
		bi_mul(x, y, &TEMP);
	}
	else                                 //  if flag != 0 -> kmul
		bi_kmul(x, y, &TEMP, flag);

	bi_assign(C, TEMP);

	if(sign == NEGATIVE)
	{
		if ((*C)->sign == NON_NEGATIVE)
			bi_flip_sign(C);
	}
	else
	{
		if ((*C)->sign == NEGATIVE)
			bi_flip_sign(C);
	}
	
	bi_delete(&TEMP);
}

void bi_squaringC(word x, bigint** C)
{
	bigint* Copy_C = NULL;
	word CT;
	word c = 0;
	word A1 = x >> (WORD_BITLEN / 2);         // x를 절반으로 나눈 앞 자리
	word A0 = x << (WORD_BITLEN / 2);         // x를 절반으로 나눈 뒷 자리
	A0 = A0 >> (WORD_BITLEN / 2);
	word C1 = A1 * A1;                        // 앞 자리끼리 곱
	word C0 = A0 * A0;                        // 뒷 자리끼리 곱
	word AA = A1 * A0;

	//   T <- T << (w/2+1)
	word T1 = AA >> ((WORD_BITLEN / 2) - 1);         
	word T0 = AA << ((WORD_BITLEN / 2) + 1);
	
	CT = C0 + T0;
	if (C0 > CT)     // carry
		c = 1;

	bi_new(&Copy_C, 2);
	Copy_C->a[1] = C1 + T1 + c;
	Copy_C->a[0] = C0 + T0;
	bi_refine(Copy_C);
	bi_assign(C, Copy_C);
	bi_delete(&Copy_C);
}

void bi_squaring(bigint* x, bigint** C)
{
	int i, j;
	bigint* C1 = NULL;
	bigint* C2 = NULL;
	bigint* T1 = NULL;
	bigint* T2 = NULL;

	bi_new(&C1, 2 * (x->wordlen));
	bi_new(&C2, 2 * (x->wordlen));
	bi_new(&T1, 2);
	bi_new(&T2, 2);

	for (j = 0; j < x->wordlen; j++)
	{
		bi_squaringC(x->a[j], &T1);                       // T1 << A_j ^2
		Left_Shift(&T1, (2 * j)*WORD_BITLEN);             // T1 <- T1 << 2jw
		bi_self_add(&C1, T1);                             // C1 <- T1 + C1
		if (j != (x->wordlen) - 1)
		{
			for (i = j + 1; i < x->wordlen; i++)
			{
				bi_mulc(x->a[j], x->a[i], &T2);            // T2 <- A_j * A_i
				Left_Shift(&T2, (i + j) * WORD_BITLEN);    // T2 <- T2 << (i+j)w
				bi_self_add(&C2, T2);                      // C2 <- add(C2, T2)
			}
		}
	}
	Left_Shift(&C2, 1);                // C2 <- C2 << 1
	bi_refine(C1);
	bi_refine(C2);
	bi_add(C1, C2, C);                // C <- add(C1, C2)
	(*C)->sign = NON_NEGATIVE;

	bi_delete(&C1);
	bi_delete(&C2);
	bi_delete(&T1);
	bi_delete(&T2);
}

void bi_ksquaring(bigint* x, bigint** C, int flag)
{
	if (flag >= x->wordlen)            // if flag >= Wordlen(A)
	{
		bi_squaring(x, C);
		return;
	}

	int l = (x->wordlen + 1) >> 1;     // l <- (Wordlen(A) +1) >> 1
	int lw = l * WORD_BITLEN;
	bigint* A0 = NULL;
	bigint* A1 = NULL;
	bi_assign(&A0, x);
	bi_assign(&A1, x);

	Right_Shift(&A1, lw);               // A1 <- |A| >> lw
	Reduction(&A0, lw);                 // A0 <- |A| mod 2^lw


	bigint* T1 = NULL;
	bigint* T0 = NULL;
	bi_new(&T1, 2 * l);
	bi_new(&T0, 2 * l);

	bi_ksquaring(A1, &T1, flag);       // T1 <- ksquaring(A1)
	bi_ksquaring(A0, &T0, flag);       // T0 <- ksquaring(A0)

	bigint* R = NULL;
	bi_new(&R, 4 * l);
	Left_Shift(&T1, 2 * lw);           
	bi_add(T1, T0, &R);                // R <- (T1 << 2lw) + T0

	bigint* S = NULL;
	bi_new(&S, 2 * l);
	bi_kmulc(A1, A0, &S);              // S <- kmul(A1, A0)
	Left_Shift(&S, lw + 1);            // S <- S << (lw + 1)

	bi_self_add(&R, S);                // R <- add(R,S)

	bi_refine(R);
	bi_assign(C, R);

	bi_delete(&A1);
	bi_delete(&A0);
	bi_delete(&T1);
	bi_delete(&T0);
	bi_delete(&S);
	bi_delete(&R);

}

void bi_ksquaringC(bigint* x, bigint** C)
{
	int sign = 0;
	bigint* TEMP = NULL;

	if (x->sign == NEGATIVE)
		bi_flip_sign(&x);

	int flag = (x->wordlen) / 2;        // flag 설정
	if(flag == 0)                       // if flag == 0 -> squaring
		bi_squaring(x, &TEMP);
	else                                // if flag != 0 -> ksquaring
		bi_ksquaring(x, &TEMP, flag);

	bi_assign(C, TEMP);
	bi_delete(&TEMP);
}
