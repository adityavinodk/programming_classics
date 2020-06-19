#include "bignum.h"

// Removes any prefix 0's before the number
void remove_breakpoint_decimal(Bignum *c)
{
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
    if (i == c->length && break_point == 0)
        c->length = 1;
}

// Parses the input string and converts it into Bignum form
void parse_string(char *s, Bignum *a)
{
    int i = 0;
    a->length = 0;
    while (i < 1000 && strcmp(&s[i], "\0") != 0)
    {
        a->A[i] = s[i] - '0';
        a->length++;
        i++;
    }
    remove_breakpoint_decimal(a);
}

// Prints the number
void print_number(Bignum *a)
{
    int i = 0;
    while (i < a->length)
    {
        printf("%d", a->A[i]);
        i++;
    }
    printf("\n");
}

// Function to return the string form of a Bignum intal
char* make_string(Bignum *a){
    char *s = malloc(sizeof(char) * a->length);
    int i = 0;
    while (i<a->length){
        s[i] = a->A[i] + '0';
        i++;
    }
    s[a->length] = '\0';
    return s;
}

// Function to return the Bignum given an intal string
Bignum* return_bignum(char* s){
    Bignum* a = malloc(sizeof(Bignum));
    parse_string(s, a);
    return a;
}

// Mutliplying by 2
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

// Adds 2 numbers
Bignum *add_numbers(Bignum *a, Bignum *b)
{
    Bignum *c = malloc(sizeof(Bignum));
    int add_pos = a->length >= b->length ? b->length - 1 : a->length - 1;
    int pos_c = a->length >= b->length ? a->length-1 : b->length-1;
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
            val = a->A[pos_a--] + carry;
            c->A[pos_c--] = val % 10;
            carry = (int)(val / 10) % 10;
        }
    }
    else if (pos_a < 0)
    {
        while (pos_b >= 0)
        {
            val = b->A[pos_b--] + carry;
            c->A[pos_c--] = val % 10;
            carry = (int)(val / 10) % 10;
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
    remove_breakpoint_decimal(c);
    return c;
}

// Defined function to add 2 numbers
char* intal_add(const char* intal1, const char* intal2){
    Bignum* a = return_bignum(intal1);
    Bignum* b = return_bignum(intal2);
    Bignum *add = add_numbers(a, b);
    char *value = make_string(add);
    free(a); free(b); free(add);
    return value;
}

// Compares two Bignum's and checks which is larger
int compare_values(Bignum *a, Bignum *b)
{
    if(!a || !b) return -2;
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

// Function to compare two numbers
int intal_compare(const char* intal1, const char* intal2){
    Bignum* a = return_bignum(intal1);
    Bignum* b = return_bignum(intal2);
    int value = compare_values(a, b);
    if(value==0) return -1;
    else if(value==1) return 1;
    return 0;
} 

// Subtract 2 numbers
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
    remove_breakpoint_decimal(c);
    return c;
}

// Defines function to calculate difference between 2 numbers
char* intal_diff(const char* intal1, const char* intal2){
    Bignum* a = return_bignum(intal1);
    Bignum* b = return_bignum(intal2);
    Bignum *sub = compare_values(a,b)? subtract_numbers(a, b): subtract_numbers(b, a);
    char *value = make_string(sub);
    free(a); free(b); free(sub);
    return value; 
}

// Initializes a Bignum variable to value 0
Bignum *initialize0()
{
    Bignum *a = malloc(sizeof(Bignum));
    a->A[0] = 0;
    a->length = 1;
    return a;
}

// Multiplying 2 Bignum's
Bignum *multiply(Bignum *a, Bignum *b)
{
    Bignum *c = initialize0();
    int pos_a = a->length - 1;
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
        c = add_numbers(c, d);
        free(d);
        free(B);
        pos_a--;
        count++;
    }
    return c;
}

// Defined function to multiply 2 numbers
char* intal_multiply(const char* intal1, const char* intal2){
    Bignum* a = return_bignum(intal1);
    Bignum* b = return_bignum(intal2);
    Bignum *mul = multiply(a, b);
    char *value = make_string(mul);
    free(a); free(b); free(mul);
    return value;
}

// Function to return Bignum of same value
Bignum *return_equal(Bignum *a){
    Bignum *b = (Bignum *)malloc(sizeof(Bignum));
    b->length = a->length;
    for(int i = 0; i<a->length; i++){
        b->A[i] = a->A[i];
    }
    return b;
}

// Function to divide 2 numbers
Bignum *division(Bignum *a, Bignum *b){
    if(compare_values(a,b)==0) return return_bignum("0");
    Bignum *d = NULL;
    Bignum *zero = return_bignum("0");
    Bignum *value = NULL;
    Bignum *rem = NULL;
    Bignum *temp = NULL;
    char *dividend = make_string(a);
    int dividend_length = a->length, string_pos = 0, dividend_pos = 0; 
    int multiple;
    char *answer = malloc(sizeof(char)*(a->length));
    int answer_pos = 0;
    char *s = NULL;
    char *s_temp = NULL;
    int compare = compare_values(b, d);
    while(dividend_pos < dividend_length){
        while((compare==1 || compare==-2) && dividend_pos < dividend_length){
            // printf("updating now\n");
            if(s){
                s_temp =(char*)malloc(sizeof(char)*string_pos);
                strcpy(s_temp, s);
                // printf("%s\n", s_temp);
                s = (char*)malloc(sizeof(char)*(string_pos+1));
                for(int i = 0; i<string_pos; i++){
                    s[i] = s_temp[i];
                }
                free(s_temp);
            }
            else{
                s = (char*)malloc(sizeof(char));
            }
            // printf("sp - %d\n", string_pos);
            s[string_pos++] = dividend[dividend_pos++];
            s[string_pos] = '\0';
            // printf("%s %lu\n", s, strlen(s));
            if(d) free(d);
            d = return_bignum(s);
            compare = compare_values(b, d);
            if(compare == 1) answer[answer_pos++] = '0';
        }
        // printf("%s\n", s);
        if(compare != 1){
            // print_number(d);
            multiple = 0;
            value = return_equal(zero);
            while(compare_values(value, d) == 0){
                temp = add_numbers(value, b);
                free(value);
                value = return_equal(temp);
                free(temp);
                multiple++;
            }
            rem = return_equal(zero);
            if(compare_values(value,d) == 1){
                temp = subtract_numbers(value, b);
                free(value);
                value = return_equal(temp);
                free(temp);
                rem = subtract_numbers(d, value);
                multiple--;
            }
            answer[answer_pos++] = '0' + multiple;
            free(s);
            // printf("multiple - %d\n", multiple);
            // printf("remainder - ");
            // print_number(rem);
            // printf("rem length - %d\n",rem->length);
            free(d);
            s = make_string(rem);
            if(compare_values(rem, zero) == 1){
                // printf("remainder string - %s\n", s);
                string_pos = rem->length;
                // printf("dividend_pos = %d\n", dividend_pos);
                d = return_bignum(s);
                // print_number(d);
            }
            else{
                d = NULL;
                string_pos = 0;
            }
            compare = compare_values(b, d);
            free(rem);
            free(value);
        }
    }
    free(zero); 
    if(d) free(d);
    // printf("%s\n", s);
    free(s);
    free(dividend);
    answer[answer_pos] = '\0';
    // printf("answer - %s\n", answer);
    return return_bignum(answer);
}

// Defined function to divide 2 numbers
char* intal_div(const char* intal1, const char* intal2){
    Bignum* a = return_bignum(intal1);
    Bignum* b = return_bignum(intal2);
    Bignum *div = division(a, b);
    char *value = make_string(div);
    free(a); free(b); free(div);
    return value;
}

// Function to calculate modulo of 2 numbers based on division
Bignum *modulo(Bignum *a, Bignum *b){
    Bignum *q = division(a, b);
    // print_number(q);
    Bignum *mul = multiply(b, q);
    Bignum *diff = subtract_numbers(a, mul);
    free(mul); free(q);
    return diff;
}

// Defined function for modulo operation
char* intal_mod(const char* intal1, const char* intal2){
    Bignum* a = return_bignum(intal1);
    Bignum* b = return_bignum(intal2);
    Bignum *mod = modulo(a, b);
    char *value = make_string(mod);
    free(a); free(b); free(mod);
    return value;
}

// Function to calculate exponent
Bignum *exponent(Bignum *a, unsigned int b)
{
    if(b == 0){
        return return_bignum("1");
    }
    Bignum *zero = return_bignum("0");
    Bignum *d = return_equal(a);
    Bignum *value = return_bignum("1");
    Bignum *temp;
    while(b>0){
        if(b%2){
            temp = value;
            value = multiply(value, d);
            free(temp);
        }
        b = b>>1;
        temp = d;
        d = multiply(d, d);
        free(temp); 
    }
    free(zero); free(d);
    return value;
}

// Defined function to compute exponent operation
char* intal_pow(const char* intal1, unsigned int n){
    if(strcmp(intal1, "0") == 0) return "1";
    Bignum* a = return_bignum(intal1);
    Bignum *pow = exponent(a, n);
    char *value = make_string(pow);
    free(a); free(pow);
    return value;
}

// Function to calculate GCD using Euclid's algorithm
Bignum* calcGCD(Bignum* a, Bignum* b){
    Bignum *zero = return_bignum("0");
    Bignum *d = return_equal(b);
    Bignum *c = return_equal(a);
    Bignum *mod;
    while(compare_values(d, zero)==1){
        mod = modulo(c, d);
        free(c);
        c = d;
        d = mod; 
    } 
    free(d); free(zero);
    return c;
} 

// Defined function to compute GCD
char* intal_gcd(const char* intal1, const char* intal2){ 
    if(strcmp(intal1, "0") == 0 && strcmp(intal2, "0") == 0) return "0";
    Bignum* a = return_bignum(intal1); 
    Bignum* b = return_bignum(intal2); 
    Bignum *gcd = compare_values(a, b)? calcGCD(a, b): calcGCD(b, a);
    char *value = make_string(gcd); 
    free(a); free(b); free(gcd); 
    return value; 
}

// Defined function to compute nth number of fibonacci series
char* intal_fibonacci(unsigned int n){
    if(n == 0) return "0";
    if(n == 1) return "1";
    int count = 1;
    Bignum *first = return_bignum("0");
    Bignum *second = return_bignum("1");
    Bignum *third = NULL;
    while(count < n){
        third = add_numbers(first, second);
        free(first);
        first = second;
        second = third;
        count++;
    }
    char *answer = make_string(third);
    free(third); free(first);
    return answer;
}

// Defined function to compute factorial of n
char* intal_factorial(unsigned int n){
    if(n==0) return "1";
    if(n==1) return "1";
    int count = n;
    char mul[5];
    Bignum *fact = return_bignum("1");
    Bignum *value;
    Bignum *temp;
    Bignum *temp2;
    while(count > 1){
        sprintf(mul, "%d", count);
        value = return_bignum(mul);
        temp = multiply(fact, value);    
        temp2 = fact;
        fact = temp;
        free(temp2);
        count--;
    }
    char *answer = make_string(fact);
    free(fact);
    return answer;
}

// Function to compare two strings
int compare_large_strings(char *a, char *b){
    int length1 = strlen(a);
    int length2 = strlen(b);
    if (length1 != length2)
    {
        return length1 > length2 ? 1 : 0;
    }
    else
    {
        for (int i = 0; i < length1; i++)
        {
            if (a[i] > b[i])
                return 1;
            else if (b[i] > a[i])
                return 0;
        }
    }
    return -1;   
}

// Defined function to compute maximum of array of intal strings
int intal_max(char **arr, int n){
    int pos = 0;
    if(n==1) return 0;
    char *maxval = arr[0];
    for(int i = 1; i < n; i++){
        if(compare_large_strings(arr[i], maxval) == 1){
            maxval = arr[i];
            pos = i;
        }
    }
    return pos;
}

// Defined function to compute minimum of array of intal strings
int intal_min(char **arr, int n){
    int pos = 0;
    if(n==1) return 0;
    char *minval = arr[0];
    for(int i = 1; i < n; i++){
        if(compare_large_strings(arr[i], minval) == 0){
            minval = arr[i];
            pos = i;
        }
    }
    return pos;
}

// Defined function for linear search of value in array of intal strings
int intal_search(char **arr, int n, const char* key){
    for(int i = 0; i < n; i++){
        if(compare_large_strings(arr[i], key)==-1){
            return i;
        }
    }
    return -1;
}

// Function for swapping two strings
void swap_strings(char **a, char **b){
    char *temp = *a;
    *a = *b;
    *b = temp;
}

// Function for Quicksort partition algorithm
int partition(char **arr, int l, int r){
    char *pivot = arr[r];
    int i = l - 1;
    for(int j = l; j<=r-1; j++){
        if(compare_large_strings(pivot, arr[j]) == 1){
            i++;
            swap_strings(&arr[i], &arr[j]);
        }
    }
    swap_strings(&arr[i+1], &arr[r]);
    return i+1;
}

// Main function for quicksort
void quicksort(char **arr, int l, int r){
    if(l<r){
        int s = partition(arr, l, r);
        quicksort(arr, l, s-1);
        quicksort(arr, s+1, r);
    }
}

// Defined function for sorting array of intal strings
void intal_sort(char **arr, int n){
    quicksort(arr, 0, n-1);
}

// Defined function for binary search of value in array of intal strings
int intal_binsearch(char **arr, int n, const char* key){
    int low = 0, high = n-1, mid, compare;
    while(low<high){
        mid = low + (high-low)/2;
        compare = compare_large_strings(arr[mid], key);
        if(compare == 1 || compare == -1) high = mid;
        else low = mid+1;
    }
    if(compare_large_strings(arr[low], key) != -1) return -1;
    return low;
}

// Function to return minimum of two numbers
int return_min(int a, int b){
    return a>b?b:a;
}

// Defined function to calculate binomial coefficient using DP
char* intal_bincoeff(unsigned int n, unsigned int k){
    Bignum **coefficients = (Bignum **)malloc(sizeof(Bignum*)*(k+1));
    for(int i = 0; i < k+1; i++){
        coefficients[i] = return_bignum("0");
    }
    coefficients[0] = return_bignum("1");
    for(int i = 1; i<=n; i++){
        for(int j = return_min(i, k); j>0; j--){
            Bignum *temp = add_numbers(coefficients[j], coefficients[j-1]);
            Bignum *temp2 = coefficients[j];
            coefficients[j] = temp;
            free(temp2);
        }
    }
    char *answer = make_string(coefficients[k]);
    free(coefficients);
    return answer;
}

// Defined function to compute maximum sum of non-consecutive values in array of intal strings
char* coin_row_problem(char **arr, int n){
    if(n==1) return arr[0];
    if(n==2) return arr[1];
    Bignum **max_coins_so_far = (Bignum **)malloc(sizeof(Bignum*)*(n));
    for(int i = 0; i < n; i++){
        max_coins_so_far[i] = (Bignum *)malloc(sizeof(Bignum));
    }
    max_coins_so_far[0] = return_bignum(arr[0]);
    max_coins_so_far[1] = return_bignum(arr[1]);
    for(int i=2; i<n; i++){
        Bignum *curr_val = return_bignum(arr[i]);
        Bignum *temp = add_numbers(max_coins_so_far[i-2], curr_val);
        free(curr_val);
        if(compare_values(temp, max_coins_so_far[i-1])==1){
            curr_val = temp;
        }
        else{
            curr_val = max_coins_so_far[i-1];
            free(temp);
        }
        max_coins_so_far[i] = curr_val;
    }
    char *answer = make_string(max_coins_so_far[n-1]);
    free(max_coins_so_far);
    return answer;
}
