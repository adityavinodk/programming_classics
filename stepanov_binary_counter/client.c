#include<stdio.h>
#include<stdlib.h>
#include "bin_counter.h"

int main()
{
    int length;
    int *numbers;
    scanf("%d", &length);
    for(int i=0; i<length; i++){
        scanf("%d", &numbers[i]);
    }
    sec_big(numbers, length);
}
