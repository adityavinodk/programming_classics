#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bignum.h"

int is_smaller(Bignum *a, Bignum *b)
{
    if (a->length != b->length)
    {
        return a->length > b->length ? 1 : 0;
    }
    else
    {
        for (int i = 0; i < a->length; i++)
        {
            if (a->A[i] > b->A[i])
                return 1;
            else if (a->A[i] < b->A[i])
                return 0;
        }
    }
    return -1;
}

Bignum *make_binary(Bignum *a)
{
    int val, carry, runTill = 1, zero_count, count = 0;
    Bignum *b = malloc(sizeof(Bignum));
    b->length = a->length;
    for (int i = 0; i < b->length; i++)
    {
        b->A[i] = a->A[i];
    }
    while (runTill)
    {
        zero_count = 0;
        carry = 0;
        for (int j = 0; j < b->length; j++)
        {
            val = carry * 10 + b->A[j];
            carry = val % 2;
            b->A[j] = val / 2;
            if (b->A[j] == 0)
                zero_count += 1;
        }
        if (zero_count == b->length)
            runTill = 0;
        a->B[count] = carry;
        count++;
    }
    int i = 0, j = count - 1, temp;
    while (i < j)
    {
        temp = a->B[i];
        a->B[i] = a->B[j];
        a->B[j] = temp;
        i++;
        j--;
    }
    a->binary_length = count;
    return a;
}

void parse_string(char *s, Bignum *a)
{
    int i = 0, j = 0;
    a->length = 0;
    while (i < 1000 && strcmp(&s[i], "\0") != 0)
    {
        a->A[i] = s[i] - '0';
        a->length++;
        i++;
    }
    a = make_binary(a);
}

void print_number(FILE *stream, Bignum *a)
{
    printf("number - ");
    int i = 0;
    while (i < a->length)
    {
        printf("%d", a->A[i]);
        i++;
    }
    printf("\n");
}

void print_binary(Bignum *a)
{
    printf("binary form - ");
    for (int i = 0; i < a->binary_length; i++)
    {
        printf("%d", a->B[i]);
    }
    printf("\n");
}

Bignum *add_numbers(Bignum *a, Bignum *b)
{
    Bignum *c = malloc(sizeof(Bignum));
    int add_pos = a->length >= b->length ? b->length - 1 : a->length - 1;
    int pos_c = a->length >= b->length ? a->length - 1 : b->length - 1;
    c->length = pos_c + 1;
    int pos_a = a->length - 1, pos_b = b->length - 1;
    int carry = 0, val;
    while (add_pos-- >= 0)
    {
        val = a->A[pos_a--] + b->A[pos_b--] + carry;
        c->A[pos_c--] = val % 10;
        carry = (int)(val / 10) % 10;
    }
    if (pos_b < 0)
    {
        while (pos_a >= 0)
        {
            c->A[pos_c--] = a->A[pos_a--] + carry;
            carry = 0;
        }
    }
    else if (pos_a < 0)
    {
        while (pos_b >= 0)
        {
            c->A[pos_c--] = b->A[pos_b--] + carry;
            carry = 0;
        }
    }
    if (carry!=0)
    {
        for (int i = c->length; i >= 0; i--)
        {
            c->A[i + 1] = c->A[i];
        }
        c->A[0] = carry;
        c->length++;
    }
    c = make_binary(c);
    return c;
}

Bignum *subtract_numbers(Bignum *a, Bignum *b)
{
    Bignum *c = malloc(sizeof(Bignum));
    Bignum *higher = is_smaller(a, b) ? a : b;
    Bignum *smaller = higher == a ? b : a;
    int sub_pos = smaller->length;
    int pos_c = higher->length - 1;
    c->length = pos_c + 1;
    int pos_higher = higher->length - 1, pos_smaller = smaller->length - 1;
    int borrow = 0;
    while (sub_pos >= 0)
    {
        c->A[pos_c] = higher->A[pos_higher] - smaller->A[pos_smaller] - borrow;
        if (c->A[pos_c] < 0)
        {
            c->A[pos_c] += 10;
            borrow = 1;
        }
        else
            borrow = 0;
        pos_higher--;
        pos_smaller--;
        pos_c--;
        sub_pos--;
    }
    if (pos_higher >= 0)
    {
        while (pos_higher >= 0)
        {
            c->A[pos_c] = higher->A[pos_higher] - borrow;
            if (c->A[pos_c] < 0)
            {
                c->A[pos_c] += 10;
                borrow = 1;
            }
            else
                borrow = 0;
            pos_higher--;
            pos_c--;
        }
    }
    int i = 0;
    int break_point = 0;
    int isFound = 0;
    while (i < c->length && !isFound)
    {
        if (c->A[i] != 0)
        {
            break_point = i;
            isFound = 1;
        }
        i++;
    }
    if (break_point > 0)
    {
        int i = break_point;
        int j = 0;
        while (i < c->length)
        {
            c->A[j] = c->A[i];
            i++;
            j++;
        }
    }
    c->length -= break_point;
    c = make_binary(c);
    return c;
}

Bignum *multiply_by_2(Bignum *a)
{
    int *B = malloc(sizeof(int) * 10000);
    int bin_len = a->length - 1, mul_carry = 0, val, pos = 0;
    while (bin_len >= 0)
    {
        val = mul_carry + (a->A[bin_len--] * 2);
        B[pos++] = val % 10;
        mul_carry = (val / 10) % 10;
    }
    if (mul_carry != 0)
        B[pos++] = mul_carry;
    for (int i = 0; i < pos; i++)
    {
        a->A[i] = B[pos - i - 1];
    }
    a->length = pos;
    free(B);
    return a;
}

// 25 = 1001 = 1*8 + 1*1 = 0 + 1 + 8

Bignum *make_decimal(Bignum *a)
{
    Bignum *mul = malloc(sizeof(Bignum));
    char *s = "1";
    int carry, rec_length = a->binary_length;
    parse_string(s, mul);
    a->A[0] = 0;
    a->length = 1;
    print_binary(a);
    for (int i = rec_length-1; i >= 0; i--)
    {
        carry = a->B[i];
        if (carry == 1)
        {
            a = add_numbers(a, mul);
        }
        mul = multiply_by_2(mul);
    }
    return a;
}

Bignum *and_bit(Bignum *a, Bignum *b)
{
    Bignum *c = malloc(sizeof(Bignum));
    int i = a->binary_length - 1, j = b->binary_length - 1;
    int lowerLength = a->binary_length < b->binary_length ? a->binary_length : b->binary_length;
    c->binary_length = lowerLength;
    int len = c->binary_length - 1;
    while (i >= 0 && j >= 0)
    {
        c->B[len--] = a->B[i--] & b->B[j--];
    }
    i = 0;
    int break_point = 0;
    int isFound = 0;
    while (i < c->binary_length && !isFound)
    {
        if (c->B[i] != 0)
        {
            break_point = i;
            isFound = 1;
        }
        i++;
    }
    if (break_point > 0)
    {
        i = break_point;
        int j = 0;
        while (i < c->binary_length)
        {
            c->B[j++] = c->B[i++];
        }
    }
    c->binary_length -= break_point;
    c = make_decimal(c);
    return c;
}

Bignum *or_bit(Bignum *a, Bignum *b)
{
    Bignum *c = malloc(sizeof(Bignum));
    int i = a->binary_length - 1, j = b->binary_length - 1;
    int higherLength = a->binary_length > b->binary_length ? a->binary_length : b->binary_length;
    c->binary_length = higherLength;
    int len = c->binary_length - 1;
    while (i >= 0 && j >= 0)
    {
        c->B[len--] = a->B[i--] | b->B[j--];
    }
    if (j < 0)
    {
        while (i >= 0)
        {
            c->B[len--] = a->B[i--];
        }
    }
    else if (i < 0)
    {
        while (i >= 0)
        {
            c->B[len--] = b->B[j--];
        }
    }
    i = 0;
    int break_point = 0;
    int isFound = 0;
    while (i < c->binary_length && !isFound)
    {
        if (c->B[i] != 0)
        {
            break_point = i;
            isFound = 1;
        }
        i++;
    }
    if (break_point > 0)
    {
        i = break_point;
        int j = 0;
        while (i < c->binary_length)
        {
            c->B[j++] = c->B[i++];
        }
    }
    c->binary_length -= break_point;
    c = make_decimal(c);
    return c;
}