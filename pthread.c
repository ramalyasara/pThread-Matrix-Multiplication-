#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <assert.h>

int SIZE, NTHREADS;
int **A, **B, **C;

void init()
{
    int i, j;

    A = (int**)malloc(SIZE * sizeof(int *));
    for(i = 0; i < SIZE; i++)
        A[i] = malloc(SIZE * sizeof(int));

    B = (int**)malloc(SIZE * sizeof(int *));
    for(i = 0; i < SIZE; i++)
        B[i] = malloc(SIZE * sizeof(int));

    C = (int**)malloc(SIZE * sizeof(int *));
    for(i = 0; i < SIZE; i++)
        C[i] = malloc(SIZE * sizeof(int));

    srand(time(NULL));

    for(i = 0; i < SIZE; i++) {
        for(j = 0; j < SIZE; j++) {
            A[i][j] = rand()%100;
            B[i][j] = rand()%100;
        }
    }
}

void mm(int tid)
{
    int i, j, k;
    int start = tid * SIZE/NTHREADS;
    int end = (tid+1) * (SIZE/NTHREADS) - 1;

    for(i = start; i <= end; i++) {
        for(j = 0; j < SIZE; j++) {
            C[i][j] = 0;
            for(k = 0; k < SIZE; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void *worker(void *arg)
{
    int tid = (int)arg;
    mm(tid);
}

int main(int argc, char* argv[])
{


	
  //int SIZE = 1024;
    pthread_t* threads;
    int rc, i;

    if(argc != 2)
    {
        printf("Usage:<number_of_threads>\n", argv[0]);
        exit(1);
    }

    SIZE = 512;
    NTHREADS = atoi(argv[1]);
    init();
    threads = (pthread_t*)malloc(NTHREADS * sizeof(pthread_t));

   

struct timespec begin, end;
double elapsed;


  

clock_gettime(CLOCK_MONOTONIC, &begin);

    for(i = 0; i < NTHREADS; i++) {
        rc = pthread_create(&threads[i], NULL, worker, (void *)i);
        assert(rc == 0);
    }

    for(i = 0; i < NTHREADS; i++) {
        rc = pthread_join(threads[i], NULL);
        assert(rc == 0);
    } 

  
clock_gettime(CLOCK_MONOTONIC, &end);

  
elapsed = end.tv_sec - begin.tv_sec;
elapsed += (end.tv_nsec - begin.tv_nsec) / 1000000000.0;
    

printf("%.10lf \n", elapsed);

    for(i = 0; i < SIZE; i++)
        free((void *)A[i]);
    free((void *)A);

    for(i = 0; i < SIZE; i++)
        free((void *)B[i]);
    free((void *)B);

    for(i = 0; i < SIZE; i++)
        free((void *)C[i]);
    free((void *)C);

    free(threads);

    return 0;
}
