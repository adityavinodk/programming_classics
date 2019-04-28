# Implementation of Stepanov's Binary Counter

## Introduction - 
1. For example: 25 20 15 x 18 10 2 = 25 18 20 15. Here, the two competing sets are 25 20 15 and 18 10 2. The biggest number is 25, and hence is printed first, post the '=' sign. Hence 25 20 15 is the winning set, and 18 10 2 is the losing set. The biggest number of the losing set is 18, and hence is printed as the second number. This is followed by all the numbers that have lost to 25(ie, 20 15), in the order as that in the winning set itself.
2. Each line in the output file represents a match played and its result, on either side of the '=' sign, according to the order of the input.
3. Output set will first have the highest of all elements of the two sets. This will be followed by the highest number in the losing set.
4. Finally, the numbers that have lost to the highest number from the winner set are printed.

## About the Program - 
1. Run the file using $CMD: 
```shell
gcc bin_counter.c <client_file_name>.c bin_counter.h
./a.out
```
2. The program takes in a set of numbers and finds the second largest element in lesser number of comparisons than the linear parsing approach.
3. Depending on the number of elements, a 2 dimensional array is made which is proportional to (logn)^2 and holds the winner set depending on the number of matches completed.
4. The idea is that the first column means 'yet to play', second column means 'won once', third column means 'won twice' and so on.
5. The 2D array automatically reconfigures itself after each match is played, to hold the winner and the ones the winner has won against. 
6. In the end, the last column holds the winner and the other players the winner has won against.

## Here is an example of sample input and outputs- 
```shell
11
20 5 15 25 10 3 56 7 98 2 68

20 5 15 25 10 3 56 7 98 2 68
20 x 5 = 20 5 
15 x 25 = 25 15 
20 5 x 25 15 = 25 20 15 
10 x 3 = 10 3 
56 x 7 = 56 7 
10 3 x 56 7 = 56 10 7 
25 20 15 x 56 10 7 = 56 25 10 7 
98 x 2 = 98 2 
98 2 x 68 = 98 68 
56 25 10 7 x 98 68 = 98 56 68
```
