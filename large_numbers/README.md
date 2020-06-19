# Multiple Precision Arithmetic Library in C

## Introduction - 
Considering the maximum value of numbers that can be stored is within 8 bytes of storage, how do you run operations on numbers of much larger value? This project aims to develop an arbitrary-precision arithmetic library which works with operands, both big and small - to store and compute operations on them. We are working with numbers of the scale of 1000 digits and run arithmetic operations such as addition, subtraction, multiplication, division, exponent, modulo and other basic logic operations. Arbitrary-precision arithmetic can also be used to avoid overflow, which is an inherent limitation of fixed-precision arithmetic. 

## Applications -  
1. Cryptography - algorithms dealing with hundreds of digits
2. Situations where overflows and artificial limits would be a bottleneck

## About the Program - 
Approach - 
The intal string is parsed and stored as a Bignum structure - an integer array of size 1000 and an integer storing the length.
1. intal_add - We perform addition by adding digits from the decimal ends of the intals, propagating the carry till the very end.
2. intal_compare - We perform a comparison of two intals based on their lengths. If the lengths are the same we compare the digits from the right-hand side, until there is a greater value. 
3. intal_diff - We perform subtraction by subtracting between digits from the decimal end, borrowing from the digit to the left if necessary. 
4. intal_multiply - We perform multiplication of intals by doing the digit multiplication technique, where the right-hand side digits of the number are multiplied with digits of the other number, with carry being propagated. These values of multiplying digits of a number with the other number are summed to return the product of 2 intals.
5. intal_mod - We perform modulo operation by first defining a function for the division of two numbers. The division is performed using a long division method where we divide the left-hand side of the numbers by the divisor till we reach a remaining value lesser than the divisor. The division function returns the integer quotient of the division. The modulo is found by dividing the 2 numbers and subtracting the quotient from the larger number. Although modulo is essentially based on division, it is much faster than the division by repeated subtraction.
6. intal_pow - We perform the exponential operation by using divide and conquer algorithm in iterative manner taking O(log n) time.
7. intal_gcd - We find the greatest common divisor in an iterative manner using Euclid's algorithm.
8. intal_fibonacci - We find the nth term of Fibonacci series by storing a 3*1 array, computing the array[2] as array[1] + array[0]. We then substitute array[0] as array[1] and array[1] as array[2]. The space complexity of this approach is O(1).
9. intal_factorial - We find the factorial by multiplying to n.
10. intal_bincoeff - We find the binomial coefficient by using dynamic programming using the property that C(n,k) = C(n-1, k-1) + C(n-1, k) obtaining a time complexity of O(n, k) and just using a single array size to compute the output in O(k) space.
11. intal_min - We find the minimum of the array of strings in linear time.
12. intal_max - We find the maximum of the array of strings in linear time.
13. intal_search - We find the element in the array of strings by performing a linear search.
14. intal_binsearch - We find the element in the sorted array using binary search in O(log n) time.
15. intal_sort - We sort the array of strings using quicksort in O(nlogn) time.

## Future Work - 
1. Calculate Product of two numbers using Strassen's Algorithm
2. Store even larger arbitrary length numbers in a structure where the strings are parsed and stored in linked list. All operations must be changed to adhere to this norm.  

## Run the file using $CMD: 
```shell
gcc bignum.c bignum.h client.c
./a.out
```
or
```shell
make
```
