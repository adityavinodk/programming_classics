#include <stdio.h>
#include <stdlib.h>
#include "bignum.h"

int main(){
    Bignum *a = malloc(sizeof(Bignum));
    char *s = malloc(sizeof(char)*1000);
    scanf("%1000s", s);
    parse_string(s, a);
    Bignum *b = malloc(sizeof(Bignum));
    char *s2 = malloc(sizeof(char)*1000);
    scanf("%1000s", s2);
    parse_string(s2, b);
    Bignum *c = malloc(sizeof(Bignum));
    // c = multiply_by_2(a);
    c = karatsuba_multiply(a,b);
    print_number(stdout, c);
    // Bignum *d = replicate(c, 0, c->length);
    // print_number(stdout, d);
}