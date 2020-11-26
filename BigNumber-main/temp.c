// test for bigint division
	printf("# SAGE code\n");
	for (int i = 0; i < check; i++) {

		while (1) {
			bi_gen_rand(&a, 0, random[i]);
			bi_gen_rand(&b, 0, random[i + 1]);
			if (Compare_ABS(a, b) >= 0)
				break;
		}

		printf("x = 0x");
		bi_show(a, 16);
		printf("\n");
		printf("y = 0x");
		bi_show(b, 16);
		printf("\n");

		DIV(a, b, &q, &r);

		printf("Q = 0x");
		bi_show(Q, 16);
		printf("\n");
		printf("R = 0x");
		bi_show(R, 16);
		printf("\n");

		printf("print((x % y == R) & (x // y) == Q)\n\n");