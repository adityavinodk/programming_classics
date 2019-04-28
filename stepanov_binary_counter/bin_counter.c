#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bin_counter.h"
#define ALLOC(type, n) malloc(sizeof(type)*n)
#define MAX(a, b) a>b?a:b  
#define MIN(a, b) a>b?b:a

int** initialize(int n){
    // Calculates the number of columns in the 2D array
    int size = (int)log2(n)+1;
    // Allocates a double pointer which points to the 2D array
    int **A = ALLOC(int*, size);
    // Each location of the 2D array is a pointer to another array which holds twice the value of the log(n)
    for(int i=0; i<size; i++){
        A[i] = ALLOC(int, 2*size);
    }
    // The first cell of each column is a count value which stores the number of contestants in the current match
    for(int i=0; i<size; i++){
        A[i][0] = 0;
    }
    return A;
}

void cleanUpStructure(int **A, int size){
    int size_array = (int)log2(size)+1;
    int i = 0;
    // Parses through the array and conducts any remaining matches between the odd elements without a contender
    while(i<size_array-1){
        if(A[i][0]==1){
            int j = i+1;
            // Finds the next element which is yet to have a contestant
            while(j<size_array-1 && A[j][0]!=1){
                j++;
            }
            int max = MAX(A[i][1], A[j][1]);
            int min = MIN(A[i][1], A[j][1]);
            // If the first element is the winner
            if(A[i][1]==max){
                // Reallocates the second column to store the details after this match
                A[j] = realloc(A[j], sizeof(size)+1);
                for(int k=1; k<=j+1; k++){
                    printf("%d ", A[j][k]);
                }
                printf("x ");
                for(int k=1; k<=i+1; k++){
                    printf("%d ", A[i][k]);
                }
                printf("= ");
                A[j][1] = max;
                printf("%d ", max);
                A[j][2] = min;
                printf("%d ", min);
                int l = 3;
                // Stores the elements that have lost to this winner
                for(int k = 2; k<i+2; k++){
                    A[j][l++] = A[i][k];
                    printf("%d ", A[i][k]);
                }
            }
            // If the second element is the winner
            else{
                // Reallocates the second column to store the details after this match
                A[j] = realloc(A[j], sizeof(size)+1);
                for(int k=1; k<=j+1; k++){
                    printf("%d ", A[j][k]);
                }
                printf("x ");
                for(int k=1; k<=i+1; k++){
                    printf("%d ", A[i][k]);
                }
                printf("= ");
                A[j][1] = max;
                printf("%d ", max);
                printf("%d ", min);
                int l = 3;
                // Stores the elements that have lost to this winner
                for(int k = 3; k<j+2; k++){
                    A[j][k] = A[j][k-1];
                    printf("%d ", A[j][k]);
                }
                A[j][2] = min;
            }
            printf("\n");
            // Starts searching after the current column
            i = j;
        }
        // Else increment column 
        else i++;
    } 
}

void printMatch(int col, int **A, int size){
    // If there is a match yet to be played between 2 contestants it updates the array with the winner of the match
    if(A[col][0]==2){
        // Calculating the winner and loser of the match
        int min = MIN(A[col][1], A[col][col+2]);
        int max = MAX(A[col][1], A[col][col+2]);
        // Stores the location of the winner and the location at which the elements must be updated
        int update_pos, winner_pos;
        // Stores the position of winner
        if(A[col][1]!=min) winner_pos = 1;
        else winner_pos = col+2;
        // Stores the position to which it must update
        if(A[col+1][0]==1){
            update_pos = col+3;
            A[col+1][0]=2;
        }
        else if(A[col+1][0]==0){
            update_pos = 1;
            A[col+1][0]=1;
        }
        int k = update_pos;
        // Stores the winner and the loser below
        A[col+1][k++] = max;
        A[col+1][k++] = min;
        // Stores the remaining elements that have lost to winner
        for(int j=winner_pos+1; j<winner_pos+col+1; j++){
            A[col+1][k++]=A[col][j];
        }
        // Prints first contestant
        for(int i=1; i<=col+1; i++){
            printf("%d ", A[col][i]);
        }
        printf("x ");
        // Prints second contestant
        for(int i=col+2; i<=2*(col+1); i++){
            printf("%d ", A[col][i]);
        }
        printf("= ");
        // Prints winner, loser and other contestants that have lost to winner
        for(int i = update_pos; i<=update_pos+col+1; i++){
            printf("%d ", A[col+1][i]);
        }
        printf("\n");
        // Reallocates the previous column
        A[col] = realloc(A[col], sizeof(int)*(size+1));
        A[col][0] = 0;    
    }
    // If the next column also has a match to be conducted recursively call the same function for that column
    if(A[col+1][0]==2) printMatch(col+1, A, size);
}

void addToArray(int val, int **A, int size){
    // Adds the current element to the 'yet to playe' column
    // If the number of elements in the column is already one, add it to the array and conduct match to update array
    if(A[0][0]==1){
        A[0][2] = val;
        A[0][0] = 2;
        printMatch(0, A, size);
    }
    // If the number of elemtns in the column is 0, just add it to the column
    else{
        A[0][1] = val;
        A[0][0] = 1;
    }
}

void sec_big(int *numbers, int length){
    int **A = initialize(length);
    // Adds each of the elements to the array
    for(int i=0; i<length; i++){
        addToArray(numbers[i], A, length);
    }
    // After the elements are added to the array is cleaned to conduct the final odd matches to decide winner
    cleanUpStructure(A, length);    
}