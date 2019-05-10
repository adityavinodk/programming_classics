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
    printf("\nlen - %d\n", a->binary_length);
}

Bignum *replicate(Bignum *a, int l, int r)
{
    Bignum *b = malloc(sizeof(Bignum));
    for (int i = 0; i < r - l; i++)
    {
        b->A[i] = a->A[l + i];
    }
    b->length = r - l;
    b = make_binary(b);
    return b;
}

Bignum *initialize0()
{
    Bignum *a = malloc(sizeof(Bignum));
    a->A[0] = 0;
    a->length = 1;
    a->B[0] = 0;
    a->binary_length = 1;
    return a;
}

void remove_breakpoint_binary(Bignum *c){
    int i = 0;
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
}

void remove_breakpoint_decimal(Bignum *c){
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
        i = break_point;
        int j = 0;
        while (i < c->length)
        {
            c->A[j++] = c->A[i++];
        }
    }
    c->length -= break_point;
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
    if (carry != 0)
    {
        for (int i = c->length; i >= 0; i--)
        {
            c->A[i + 1] = c->A[i];
        }
        c->A[0] = carry;
        c->length++;
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

Bignum *subtract_numbers(Bignum *a, Bignum *b)
{
    Bignum *c = malloc(sizeof(Bignum));
    Bignum *higher = a;
    Bignum *smaller = b;
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

Bignum *multiply(Bignum *a, Bignum *b)
{
    Bignum *c = initialize0();
    int pos_a = a->length - 1, val;
    int count = 0;
    while (pos_a >= 0)
    {
        int *B = malloc(sizeof(int) * 10000);
        int mul_carry = 0, val, b_len = b->length - 1, pos = 0;
        while (b_len >= 0)
        {
            val = mul_carry + (b->A[b_len--] * a->A[pos_a]);
            B[pos++] = val % 10;
            mul_carry = (val / 10) % 10;
        }
        if (mul_carry != 0)
            B[pos++] = mul_carry;
        Bignum *d = initialize0();
        for (int i = 0; i < pos; i++)
            d->A[i] = B[pos - i - 1];
        for (int i = pos; i < pos + count; i++)
            d->A[i] = 0;
        d->length = pos + count;
        d = make_binary(d);
        c = add_numbers(c, d);
        free(d);
        free(B);
        pos_a--;
        count++;
    }
    return c;
}

Bignum *make_decimal(Bignum *a)
{
    Bignum *mul = malloc(sizeof(Bignum));
    char *s = "1";
    int carry, rec_length = a->binary_length;
    parse_string(s, mul);
    a->A[0] = 0;
    a->length = 1;
    for (int i = rec_length - 1; i >= 0; i--)
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
    remove_breakpoint_binary(c);
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
    remove_breakpoint_binary(c);
    c = make_decimal(c);
    return c;
}

void makeEqualLength(Bignum *a, Bignum *b)
{
    int len1 = a->length;
    int len2 = b->length;
    if (len1 < len2)
    {
        for (int i = len2 - len1 - 1; i >= 0; i--)
            a->A[i + 1] = a->A[i];
        for (int i = 0; i < len2 - len1; i++)
            a->A[i] = 0;
    }
    else if (len1 > len2)
    {
        for (int i = len1 - len2 - 1; i >= 0; i--)
            b->A[i + 1] = b->A[i];
        for (int i = 0; i < len1 - len2; i++)
            b->A[i] = 0;
    }
}

Bignum *karatsuba_multiply(Bignum *a, Bignum *b)
{
    Bignum *c = malloc(sizeof(Bignum));

    makeEqualLength(a, b);
    int n = a->length;

    // Base cases
    if (n == 0)
        return 0;
    if (n == 1)
        return multiply(a, b);
    if (n % 2)
    {
        for (int i = n - 1; i >= 0; i--)
        {
            a->A[i + 1] = a->A[i];
            b->A[i + 1] = b->A[i];
        }
        a->A[0] = 0;
        b->A[0] = 0;
        a->length++;
        b->length++;
        n++;
    }

    int m = n / 2;

    Bignum *a1 = replicate(a, 0, m);
    Bignum *a2 = replicate(a, m, n);
    Bignum *b1 = replicate(b, 0, m);
    Bignum *b2 = replicate(b, m, n);

    Bignum *p1 = karatsuba_multiply(a1, b1);
    Bignum *p2 = karatsuba_multiply(a2, b2);
    Bignum *p3 = karatsuba_multiply(add_numbers(a1, a2), add_numbers(b1, b2));

    Bignum *larger_power_of_10 = malloc(sizeof(Bignum));
    Bignum *smaller_power_of_10 = malloc(sizeof(Bignum));
    for (int i = 0; i < n; i++)
        larger_power_of_10->A[i + 1] = 0;
    larger_power_of_10->A[0] = 1;
    larger_power_of_10->length = n + 1;
    larger_power_of_10 = make_binary(larger_power_of_10);

    for (int i = 0; i < m; i++)
        smaller_power_of_10->A[i + 1] = 0;
    smaller_power_of_10->A[0] = 1;
    smaller_power_of_10->length = m + 1;
    smaller_power_of_10 = make_binary(smaller_power_of_10);

    Bignum *first = multiply(p1, larger_power_of_10);
    Bignum *second = subtract_numbers(p3, add_numbers(p1, p2));
    second = multiply(second, smaller_power_of_10);
    Bignum *third = add_numbers(first, second);
    c = add_numbers(third, p2);

    free(a1);
    free(a2);
    free(b1);
    free(b2);
    free(p1);
    free(p2);
    free(p3);
    free(smaller_power_of_10);
    free(larger_power_of_10);
    free(first);
    free(second);
    free(third);
    return c;
}

void shift_left(int *A, int *Q, int length)
{
    for (int i = 0; i < length; i++)
    {
        A[i] = A[i + 1];
    }
    A[length] = Q[0];

    for (int i = 0; i < length - 1; i++)
    {
        Q[i] = Q[i + 1];
    }
}

int *add_bits(int *a, int *b, int length)
{
    int c = 0;
    int *val = malloc(sizeof(int) * length);
    for (int i = length; i >= 0; i--)
    {
        val[i] = a[i] ^ b[i] ^ c;
        c = ((a[i] & b[i]) | (a[i] & c)) | (b[i] & c);
    }
    return val;
}

int *subtract_bits(int *a, int *b, int length)
{
    int *c = malloc(sizeof(int) * length);
    for (int i = 0; i < length; i++)
    {
        if (b[i])
            c[i] = 0;
        else
            c[i] = 1;
    }
    int *d = malloc(sizeof(int) * length);
    for (int i = 0; i < length - 1; i++)
        d[i] = 0;
    d[length - 1] = 1;
    c = add_bits(c, d, length);
    free(d);
    return add_bits(a, c, length);
}

Bignum *division(Bignum *a, Bignum *b)
{
    int length = a->binary_length;
    int n = length;
    int *M = malloc(sizeof(int) * (length + 1));
    int diff_length = length - b->binary_length;
    int *temp = malloc(sizeof(int) * length);
    for (int i = b->binary_length - 1; i >= 0; i--)
        temp[i + diff_length] = b->B[i];
    for (int i = 0; i < diff_length; i++)
        temp[i] = 0;
    for (int i = 0; i < length; i++)
        M[i + 1] = temp[i];
    M[0] = 0;
    int *A = malloc(sizeof(int) * (length + 1));
    for (int i = 0; i < length + 1; i++)
        A[i] = 0;
    int *Q = malloc(sizeof(int) * length);
    for (int i = 0; i < length; i++)
        Q[i] = a->B[i];
    while (n != 0)
    {
        shift_left(A, Q, length);
        if (A[0] == 0) A = subtract_bits(A, M, length + 1);
        else A = add_bits(A, M, length + 1);

        if (A[0] == 1)
            Q[length - 1] = 0;
        else
            Q[length - 1] = 1;
        n--;
    }
    if (A[0])
        A = add_bits(A, M, length + 1);
    Bignum *c = malloc(sizeof(Bignum));
    for (int i = 0; i < length; i++)
        c->B[i] = Q[i];
    c->binary_length = length;
    remove_breakpoint_binary(c);
    c = make_decimal(c);
    Bignum *d = malloc(sizeof(Bignum));
    for(int i = 0; i<length+1; i++)
        d->B[i] = A[i];
    d->binary_length = length+1;
    remove_breakpoint_binary(d);
    d = make_decimal(d);
    return c;
}