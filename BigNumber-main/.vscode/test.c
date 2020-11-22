#include "1011big_num_header.h"
// 덧셈과 뺄셈 구현

// bigint 덧셈
void bi_add(bigint* x, bigint* y, bigint** C)
{
    int flag, flag_l;   // flag_l은 max_wordlen(x, y)
                        // wordlen x > y 이면 flag = 1, 그외에는 flag = 0;

    int l = x->wordlen + y->wordlen + 1;    // 덧셈 워드길이의 상한

    if(x->wordlen > y->wordlen){
        flag = 1;
        flag_l = x->wordlen;
    }
    else if(x->wordlen < y->wordlen){
        flag = 0;
        flag_l = y->wordlen;
    }
    else{
        flag = -1;
        flag_l = x->wordlen;

    }
    

    bi_new(C, l);

    int c = 0;
    // int word_modulo = (1 << WORD_BITLEN) - 1;

    // 겹치는 부분에 대해서 X + Y 수행
    for(int i = 0; i < flag_l; i++)
    {
        int c_1 = 0;
        (*C)->a[i] = (x->a[i] + y->a[i]) % word_modulo ;

        if((*C)->a[i] < x->a[i])
            c_1 = 1;
        
        (*C)->a[i] = ((*C)->a[i] + c) % word_modulo;

        if((*C)->a[i] < c)
            c_1 += 1;

        c = c_1;
    }

    // X, Y 의 워드길이가 다른 경우, X + 0(or Y + 0) 수행
    if(flag == 1) {
        for(int i = flag_l; i < x->wordlen; i++)
        {
            int c_1 = 0;
            (*C)->a[i] = x->a[i];

            (*C)->a[i] = ((*C)->a[i] + c) % word_modulo;    
            
            if((*C)->a[i] < c)
                c_1 += 1;        
            
            c = c_1;
        }
    }
    else if(flag == 0) {
        for(int i = flag_l; i < y->wordlen; i++)
        {
            int c_1 = 0;
            (*C)->a[i] = y->a[i];

            (*C)->a[i] = ((*C)->a[i] + c) % word_modulo;    
            
            if((*C)->a[i] < c)
                c_1 += 1;        
            
            c = c_1;
        }
    }

    if(c == 1)
        (*C)->a[l-1] = 1;

    bi_refine(*C);
    
}


// bigint 뺄셈
void bi_subc(bigint* x, bigint*y, bigint ** C)  // x >= y > 0 에서 x - y
{
    int b = 0;

    for(int i = 0; i < y->wordlen; i++)
    {
        (*C)->a[i] = (x->a[i] - b) % word_modulo;
        if(x->a[i] < b)
            b = 1;
        else
            b = 0;
        
        if((*C)->a[i] < y->a[i])
            b += 1;

        (*C)->a[i] = (*C)->a[i] - y->a[i] % word_modulo;
        
    }
}

void bi_sub(bigint* x, bigint*y, bigint** C)
{
    (*C)->sign = 0;     // 기본적으로 양수로 세팅

    if(is_zero(x) == 0)
    {
        bi_assign(C, y);
        bi_flip_sign(C);    // -Y를 리턴
    }
    else if(is_zero(y) == 0)
    {
        bi_assign(C, x);    // X를 리턴
    }
    
    if(x->sign == 0 && y->sign == 0)    // x, y 둘다 양수
    {
        if(Compare_ABS(x, y) == 1)  // x > y > 0
        {
            bi_subc(x, y, C);
        }
        else if(Compare_ABS(x, y) == 0) // x == y > 0
        {
            bi_set_zero(C);
        }
        else if(Compare_ABS(x, y) == -1)    // y > x > 0
        {
            bi_subc(y, x, C);
            bi_flip_sign(C);
        }
    }
    else if(x->sign != y->sign) // 둘 중 한개만 양수
    {
        if(x->sign = 0) // x > 0, y < 0
        {
            bi_add(x, y, C);    // add에서 sign을 사용하지 않는다.
        }
        else    // x < 0, y > 0
        {
            bi_add(x, y, C);
            bi_flip_sign(C);
        }
    }
    else if(x->sign == -1 && y->sign == -1)
    {
        if(Compare_AB(x, y) == 1)      // * 안넣는게 맞나? ㅠ
        {
            bi_subc(y, x, C);
        }
        else if(Compare_AB(x, y) == 0)
        {
            bi_set_zero(C);
        }
        else if(Compare_ABS(x, y) == -1)
        {
            bi_subc(x, y, C);
            bi_flip_sign(C);
        }
    }

}


















