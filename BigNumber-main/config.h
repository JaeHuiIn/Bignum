#define WORD_BITLEN 8

#if WORD_BITLEN == 8
typedef unsigned char word;
#define WORD_MASK 0xff; 
#elif WORD_BITLEN == 32
typedef unsigned int word;
#define WORD_MASK 0xffffffff; 
#elif WORD_BITLEN == 64
typedef unsigned long long word;
#define WORD_MASK 0xffffffffffffffff; 
#endif 

#define ZERORIZE