#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>      // for seed
#include<time.h>        // for seed

void swap(int* x, int* y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

/**
 * This function returns random number within given range without breaking randomness of the rand() function.
 * Never use number = min + rand() % (max - min) this one because of mod operations removes uniformity of the distribution.
 */
int getRandom(int min, int max){
    double randomNumber = (double)rand() / RAND_MAX;        // first get random number between 0 and 1
    return min + ( randomNumber * (max - min) );            // then multiply by desired range
}

/**
 * Fairly randomizes the given array
 */
void randomize(int arr[], int n){
    int i, j;
    for( i = 0; i < n; i++){
        j = getRandom(i,n-1);
        swap(&arr[i], &arr[j]);
    }
}

int main(){
    
    time_t t;
    srand((unsigned)time(&t) * getppid() * (unsigned)&t );
    int i;
    int A[] = {0,1,2,3,4,5,6,7,8,9};

    randomize(A, 10);
    for( i = 0; i < 10; i++ )
        printf("%d ", A[i]);

    /*
    for( i = 0; i < 200; i++ )
        printf("\n%d", getRandom(5,10));
    */

    return 0;
}

