void div_test()
{
	int check, upper_limit, lower_limit;
	printf("enter number for check(press 1 for basic setting): ");
	scanf("%d", &check);
	if (check == 1) {
		check = 50;
		upper_limit = 50;
		lower_limit = 30;
	}
	else {
		printf("enter upper limit: ");
		scanf("%d", &upper_limit);
		printf("enter lower limit: ");
		scanf("%d", &lower_limit);
		printf("\n");
	}


	int random[1000] = { 0, };

	// create integer for random wordlen. sign is always POSITIVE
	for (int i = 0; i < check + 1; i++) {
		while (1) {
			random[i] = rand() % upper_limit;
			if (random[i] >= lower_limit)
				break;
		}
	}

	int choose;
	printf("Choose your work\n1. School book division \n2. School book Binary Long Division \n3. Multi-Pricision Long Division\n");
	scanf("%d", &choose);
	bigint* A = NULL;
	bigint* B = NULL;
	bigint* Q = NULL;
	bigint* R = NULL;
	clock_t start = clock();


	if (choose == 1) {
		// test for school book division
		printf("# SAGE code\n");
		for(int i = 0; i < check; i++) {
			while(1) {
				bi_gen_rand(&A, 0, random[i]);
				bi_gen_rand(&B, 0, random[i + 1]);
				if(Compare_ABS(A, B) >= 0)
					break;
			}

			printf("x = 0x");
			bi_show(A, 16);
			printf("\n");
			printf("y = 0x");
			bi_show(B, 16);
			printf("\n");

			bi_sb_div(A, B, &Q, &R);

			printf("Q = 0x");
			bi_show(Q, 16);
			printf("\n");
			printf("R = 0x");
			bi_show(R, 16);
			printf("\n");

			printf("print((x %% y == R) & (x // y) == Q)\n\n");
		}

	}
	else if (choose == 2) {
		// test for school book B_L_D
		printf("# SAGE code\n");
		for(int i = 0; i < check; i++) {
			while(1) {
				bi_gen_rand(&A, 0, random[i]);
				bi_gen_rand(&B, 0, random[i + 1]);
				if(Compare_ABS(A, B) >= 0)
					break;
			}

			printf("x = 0x");
			bi_show(A, 16);
			printf("\n");
			printf("y = 0x");
			bi_show(B, 16);
			printf("\n");

			Binary_Long_Division(A, B, &Q, &R);

			printf("Q = 0x");
			bi_show(Q, 16);
			printf("\n");
			printf("R = 0x");
			bi_show(R, 16);
			printf("\n");

			printf("print((x %% y == R) & (x // y) == Q)\n\n");
		}


	}
	else if (choose == 3) {
		// test for multi-pricision Division
		int ran1;
		int ran2;
		printf("# SAGE code\n");
		for(int i = 0; i < check; i++) {
			while (1) {
				ran1 = rand() % check;
				ran2 = (ran1 + 1) % check;

				bi_gen_rand(&A, 0, random[ran1]);
				bi_gen_rand(&B, 0, random[ran2]);

				if (Compare_ABS(A, B) >= 0)
					break;
			}
			printf("x = 0x");
			bi_show(A, 16);
			printf("\n");
			printf("y = 0x");
			bi_show(B, 16);
			printf("\n");
			DIV(A, B, &Q, &R);
			printf("Q = 0x");
			bi_show(Q, 16);
			printf("\n");
			printf("R = 0x");
			bi_show(R, 16);
			printf("\n");

			printf("print((x %% y == R) & ((x // y) == Q))\n\n");
			//printf("55555555555555555\n");

		}


	}
	else
		printf("You choose wrong number\n");
	
	clock_t end = clock();
	printf("Time : %lf\n", (double)(end - start) / CLOCKS_PER_SEC);

	bi_delete(&A);
	bi_delete(&B);
	bi_delete(&Q);
	bi_delete(&R);

}