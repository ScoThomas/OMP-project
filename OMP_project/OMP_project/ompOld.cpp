
	/*
	Preformance with 200*10 matrix with 1 thread = t1 278,t2 255,t3 264
	2 thread = t1 303,t2 266,t3 258
	4 thread = t1 281,t2 280,t3 287
	6 thread = t1 278,t2 286,t3 278
	8 thread = t1 287,t2 280,t3 278
	16 thread = t1 296,t2 316,t3 316
	32 thread = t1 326,t2 314,t3 338
	*/
	/*
	static const int N = 200;
	static const int M = 10;
	static const int T = 4; 
	clock_t start;
	clock_t end;

	omp_set_num_threads(T);
	srand(time(NULL));

	int inputVector[N];
	int matrix[N][N];
	int outputVector[M];


	for (int i = 0; i < N;i++){
	inputVector[i] = rand() %20;
	}

	for (int i = 0; i < N;i++)
	for (int j = 0; j < M;j++)
	matrix[i][j] = rand() % 20; 


	//Start time measurement for critical section
	start = clock();


	#pragma omp parallel for
	for (int i = 0; i < N;i++){

	outputVector[i] = 0;

	for (int j = 0; j < M;j++)
	{
	//printf("nthreads %d\n", omp_get_num_threads());   debug code
	outputVector[i] += matrix[i][j] * inputVector[j];
	}
	}

	//End time measurement for critical section
	end = clock();


	#pragma omp parallel 
	printf("Hello from thread %d, nthreads %d\n", omp_get_thread_num(), omp_get_num_threads());

	printf("The vector is\n");

	for(int i = 0; i < M; i++){
	printf("%d\n", outputVector[i]);
	}

	printf("nthreads %d\n", omp_get_num_threads());
	printf("The program took %d clock cycles", end-start);


	Sleep(10000);
	*/
