#include <stdio.h>
#include <stdlib.h>
#include "bignum.h"

int main(){
    Bignum *a = malloc(sizeof(Bignum));
    printf("Enter a - ");
    char *s = malloc(sizeof(char)*1000);
    scanf("%1000s", s);
    parse_string(s, a);
    Bignum *b = malloc(sizeof(Bignum));
    printf("Enter b - ");
    char *s2 = malloc(sizeof(char)*1000);
    scanf("%1000s", s2);
    parse_string(s2, b);
    Bignum *add = add_numbers(a,b);
    Bignum *sub = subtract_numbers(a,b);
    Bignum *mul = karatsuba_multiply(a,b);
    Bignum *divide = division(a,b);
    Bignum *and_bits = and_bit(a,b);
    Bignum *or_bits = or_bit(a,b);
    printf("\nAdditiion - ");
    print_number(add);
    printf("\nSubtraction - ");
    print_number(sub);
    printf("\nMutlitpliication - ");
    print_number(mul);
    printf("\nDivision - ");
    print_number(divide);
    printf("\nAND - ");
    print_number(and_bits);
    printf("\nOR - ");
    print_number(or_bits);
}