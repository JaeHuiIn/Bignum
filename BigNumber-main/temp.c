#include <stdio.h>

int main()
{

	int n = 3;
	int bit[2049] = {0, };
    int n_temp = n;

    int j = 0;

    while(n_temp >= 1) {
        bit[j] = n_temp & 0x01;

        j += 1;
        n_temp = n_temp >> 1;

    }

	for(int i = 2; i >= 0; i--)
		printf("%d ", bit[i]);
	printf("\n");

	return 0;
}