#include <math.h>    // sqrt
#include <stdio.h>   // printf
#include <stdlib.h>  // atoi, malloc, free, exit, NULL
#include <stdbool.h> // bool

#include <pthread.h>

#define DEBUG 0
#define VERBOSE 0

#define NUM_THREADS 8

long num;
double sqrt_num;

bool* is_prime;

void * prime_seive_multiple(void* args);

/*
 * Input should be a single number
 */
int main(int argc, char *argv[])
{
    if( argc < 2 )
    {
        printf("No arguments passed, require a number to check.\n");
        exit(1);
    }

    /*
     * Take input number, convert to an integer
     */
    num = atol(argv[1]);
    sqrt_num = sqrt(num);

    if( DEBUG )
        printf("N: %ld, S: %.2f\n", num, sqrt_num);

    ///////////////////////////// END ARGS /////////////////////////////////////

    ///////////////////////////// INIT /////////////////////////////////////////

    is_prime = malloc (sizeof(bool) * num);

    if(is_prime == NULL)
    {
        printf("Error Malloc-ing array");
        exit(-1);
    }

    if( DEBUG )
        printf("Array Created\n");

    for(long ii = 0; ii < num; ii++)
    {
        is_prime[ii] = true;
    }

    if( DEBUG )
        printf("All set to 1\n");

    is_prime[0] = false;
    is_prime[1] = false;

    // END INIT

    pthread_t threads[NUM_THREADS];

    for(int jj = 0; jj < NUM_THREADS; jj++)
    {
        pthread_create(&threads[jj], NULL, &prime_seive_multiple, (void *) jj );
    }

    // SEIVE

    // END SEIVE

    for(int jj = 0; jj < NUM_THREADS; jj++)
    {
        pthread_join(threads[jj], NULL);
    }

    // OUTPUT

    long count = 0;

    for(long pp = 0; pp < num; pp++)
    {
        if(is_prime[pp])
            count++;
    }

    printf("There are %ld primes under %ld\n", count, num);

    // END OUTPUT

    // CLEAN UP
    free(is_prime);

    return 0;
}

void * prime_seive_multiple(void* args)
{
    int id = (int) args + 1;

    int range = num - 1;

    int excess = range % NUM_THREADS;
    int num_itr = range / NUM_THREADS;

    int start;

    if( id > NUM_THREADS - excess )
        start = 2 + ((NUM_THREADS - excess)*(num_itr)) + ((id-(NUM_THREADS-excess+1))*(num_itr+1));
    else
        start = 2 + ((id-1)*num_itr);

    if( id > NUM_THREADS - excess)
        num_itr++;

    printf("Thread %d, starting at %d, runnning %d times[excess=%d]\n", id, start, num_itr, excess);

    for(long ii = 0 ; ii < num_itr; ii++)
    {
        long jj = start + ii;

        if( !is_prime[jj] )
            continue;

        if( DEBUG )
            printf("loop itteration: %ld\n", jj);

        for(long kk = jj*jj; kk < num; kk+=jj)
        {
            is_prime[kk] = false;
        }

    }


    pthread_exit(0);
}
