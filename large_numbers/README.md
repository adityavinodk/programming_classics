# Multiple Precision Arithmetic Library in C

## Introduction - 
Considering the maximum value of numbers that can be stored is within 8 bytes of storage, how do you run operations on numbers of much larger value? This project aims to develop an arbitrary-precision arithmetic library which works with operands, both big and small - to store and compute operations on them. We are working with numbers of the scale of 100 digits and run basic operations such as addition, subtraction, multiplication, division and basic logic operations. Arbitrary-precision arithmetic can also be used to avoid overflow, which is an inherent limitation of fixed-precision arithmetic. 

## About the Program - 
1.	Takes large scale numbers as string inputs
2.	The structure which will store the values will have an array and a length counter, an and array with the binary form of the number
3.	Addition and Subtraction operations are carried by the long method with carry and borrow respectively 
4.	For larger operations like multiplication, a pointer to a linked list is used for the Karatsuba algorithm.
5.	The division operation is done using the non-restoring division method using the bit values of the numbers.
6.	All basic logic operations are done using the binary form of the numbers.