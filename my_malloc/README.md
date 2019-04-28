# Implementation of first fit mymalloc function using character array

## About the Program - 
1. Run the file using $CMD: 
```shell
gcc my_malloc.c <client_file_name>.c my_malloc.h
./a.out
```
2. The implementation is done using pointer to character array where each block is made record of using a bookkeeping block of 6 bytes. 
3. A cleanup code is run to manage the redundant bookkeeping blocks by removing the bookkeeping for consecutive blocks of free status
4. In first fit, the first block which is larger than or equal to the needed size is allocated.