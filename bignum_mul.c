#include "bignum_mul.h"

void bi_mulc(word x, word y, bigint** C)
{
	//�̰� word�� �Ѱ� �� bigint�� �����ؼ� �������� delete�� �ؾ��ϳ�?
	word R_x = x >> (WORD_BITLEN / 2);      // x�� �������� ���� �� �ڸ�
	word L_x = x % (2 << (WORD_BITLEN / 2));// x�� �������� ���� �� �ڸ�
	word R_y = y >> (WORD_BITLEN / 2);      // y�� �������� ���� �� �ڸ�
	word L_y = y % (2 << (WORD_BITLEN / 2));  // y�� �������� ���� �� �ڸ�
	word A1, A0, AA1, AA0;  //����� ���� ������ ��
	word c = 0;
	A1 = R_x * R_y; // �� �ڸ����� ��
	A0 = L_x * L_y; // �� �ڸ����� ��
	AA1 = ((R_x * L_y) + (L_x * R_y)) >> (WORD_BITLEN / 2); // �밢�� ���� ���ڸ�
	AA0 = ((R_x * L_y) + (L_x * R_y)) << (WORD_BITLEN / 2); // �밢�� ���� ���ڸ�

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
	int max_len = x->wordlen + y->wordlen;  //C�� �ִ� ����
	bigint* C_word = NULL;
	bi_new(C, max_len);   // max_len ���Ƿ� ���� 
	bi_new(&C_word, 2);   // x->a[i] * y->a[j]�� �����ص� ����

	for (int i = 0; i < x->wordlen; i++)
	{
		for (int j = 0; j < y->wordlen; j++)
		{
			bi_mulc(x->a[i], y->a[j], &C_word);          // �� ���徿 ��
			Left_Shift(&C_word, WORD_BITLEN * (i + j));  // ����� �� ��ġ�� ����
			(*C)->a[C_word->wordlen - 1] = (*C)->a[C_word->wordlen - 1] + C_word->a[C_word->wordlen - 1];  // ����
			if (C_word->wordlen != 1)
				(*C)->a[C_word->wordlen - 2] = (*C)->a[C_word->wordlen - 2] + C_word->a[C_word->wordlen - 2];  //����
		}
	}
	if (x->sign == y->sign)         //��ȣ ���߱�
		(*C)->sign = NON_NEGATIVE;
	else
		(*C)->sign = NEGATIVE;
	bi_delete(&C_word);
}