#include <stdlib.h>
#include <stdio.h>

typedef struct bignumber{
    int A[1000];
    int B[10000];
    int length;
    int binary_length;
}Bignum;

void parse_string(char *s, Bignum *a);
void print_number(Bignum *a);
Bignum* add_numbers(Bignum *a, Bignum *b);
Bignum* subtract_numbers(Bignum *a, Bignum *b);
Bignum* and_bit(Bignum *a, Bignum *b);
Bignum* or_bit(Bignum *a, Bignum *b);
Bignum* karatsuba_multiply(Bignum *a,Bignum *b);
Bignum* division(Bignum *a, Bignum *b);