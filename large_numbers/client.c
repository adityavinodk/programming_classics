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
    c = or_bit(a, b);
    // c = subtract_numbers(a, b);
    // // printf("%d\n", c->length);
    print_number(stdout, c);
    // printf("\n");
}