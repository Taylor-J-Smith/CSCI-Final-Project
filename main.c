#include <math.h>    // sqrt
#include <stdio.h>   // printf
#include <stdlib.h>  // atoi, malloc, free, exit, NULL
#include <stdbool.h> // bool

#define DEBUG 0
#define VERBOSE 0

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
    long num = atol(argv[1]);
    double sqrt_num = sqrt(num);

    if( DEBUG )
        printf("N: %ld, S: %.2f\n", num, sqrt_num);

    ///////////////////////////// END ARGS /////////////////////////////////////

    ///////////////////////////// INIT /////////////////////////////////////////

    bool* is_prime = malloc (sizeof(bool) * num);

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

    // SEIVE

    for(long jj = 2; jj < sqrt_num; jj++)
    {
        if( !is_prime[jj] )
            continue;

        if( DEBUG )
            printf("loop itteration: %ld\n", jj);

        for(long kk = jj*jj; kk < num; kk+=jj)
        {
            is_prime[kk] = false;
        }

    }

    // END SEIVE

    // OUTPUT

    long count = 0;

    for(long pp = 0; pp < sqrt_num; pp++)
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
