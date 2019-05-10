#include <stdio.h>
#include <stdlib.h>
#include "bignum.h"

int main()
{
    int pow;
    Bignum *a = malloc(sizeof(Bignum));
    printf("Enter a - ");
    char *s = malloc(sizeof(char) * 1000);
    scanf("%1000s", s);
    parse_string(s, a);
    Bignum *b = malloc(sizeof(Bignum));
    printf("Enter b - ");
    char *s2 = malloc(sizeof(char) * 1000);
    scanf("%1000s", s2);
    parse_string(s2, b);
    printf("\nAdditiion - ");
    Bignum *add = add_numbers(a, b);
    print_number(add);
    free(add);
    printf("\nSubtraction - ");
    Bignum *sub = subtract_numbers(a, b);
    print_number(sub);
    free(sub);
    printf("\nMutlitpliication - ");
    Bignum *mul = karatsuba_multiply(a, b);
    print_number(mul);
    free(mul);
    printf("\nDivision - ");
    Bignum *divide = division(a, b);
    if (divide){
        print_number(divide);
        free(divide);
    }
    else
        printf("not defined\n");
    printf("\nAND - ");
    Bignum *and_bits = and_bit(a, b);
    print_number(and_bits);
    free(and_bits);
    printf("\nOR - ");
    Bignum *or_bits = or_bit(a, b);
    print_number(or_bits);
    free(or_bits);
    printf("\na^pow - Enter power - ");
    scanf("%d", &pow);
    Bignum *expo = exponent(a, pow);
    print_number(expo);
}