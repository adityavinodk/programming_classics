#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Define structure for Big Number
typedef struct bignumber{
    int A[1000];
    int length;
}Bignum;

// Library "intal" - Integer of arbitray length
// intal is a nonnegative integer of arbitrary length (not more than 1000 decimal digits).
// The integer is stored as a null terminated string of ASCII characters.
// String of decimal digits ('0' thru '9') are stored in big endian style.
// That is, the most significant digit is at the head of the string.
// Eg: Integer 25 is stored in str as '2' at str[0], '5' at str[1], and null char at str[2].

// Returns the sum of two intals.
char* intal_add(const char* intal1, const char* intal2);

// Returns the comparison value of two intals.
// Returns 0 when both are equal.
// Returns +1 when intal1 is greater, and -1 when intal2 is greater.
int intal_compare(const char* intal1, const char* intal2);

// Returns the difference (obviously, nonnegative) of two intals.
char* intal_diff(const char* intal1, const char* intal2);

// Returns the product of two intals.
char* intal_multiply(const char* intal1, const char* intal2);
char* intal_div(const char* intal1, const char* intal2);

// Returns intal1 mod intal2 in O(log intal1) time complexity
// intal2 > 1
char* intal_mod(const char* intal1, const char* intal2);

// Returns intal1 ^ intal2 in O(log n) time
char* intal_pow(const char* intal1, unsigned int n);

// Returns Greatest Common Devisor of intal1 and intal2 using Euclid's algorithm
// GCD is "0" if both intal1 and intal2 are "0" even though it is undefined, mathematically.
char* intal_gcd(const char* intal1, const char* intal2);

// Returns nth fibonacci number.
// intal_fibonacci(0) = intal "0".
// intal_fibonacci(1) = intal "1".
char* intal_fibonacci(unsigned int n);

// Returns the factorial of n
char* intal_factorial(unsigned int n);

// Returns the Binomial Coefficient C(n,k) using DP
// 0 <= k <= n
char* intal_bincoeff(unsigned int n, unsigned int k);

// Returns the offset of the largest intal in the array.
// Returns the smallest offset if there are multiple occurrences.
// 1 <= n <= 1000
int intal_max(char **arr, int n);

// Returns the offset of the smallest intal in the array.
// Returns the smallest offset if there are multiple occurrences.
// 1 <= n <= 1000
int intal_min(char **arr, int n);

// Returns the offset of the first occurrence of the key intal in the array.
// Returns -1 if the key is not found.
// 1 <= n <= 1000
int intal_search(char **arr, int n, const char* key);

// Returns the offset of the first occurrence of the key intal in the SORTED array in O(log n) time
// Returns -1 if the key is not found.
// The input array is sorted in nondecreasing order.
// 1 <= n <= 1000
int intal_binsearch(char **arr, int n, const char* key);

// Sorts the array of n intals in O(nlogn) time
// 1 <= n <= 1000
void intal_sort(char **arr, int n);
