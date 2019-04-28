#include <stdlib.h>
#include <stdio.h>
#include "my_malloc.h"

// performing first fit operation
// Each bookkeeaping block consists of 6 bytes with 4 bytes for storing the size of the block, 
// 2 bytes for storing the status of the block 
char *p;

void allocate(int n){
    p = realloc(p, sizeof(char)*n);
    // Initializing a integer pointer to the array for storing integers
    int *a = (int*)p;
    *(a+1) = (short)0;
    *a = n-10;
    // Storing a block to show the end of the array with block_size = -1
    int *b = (int*)&p[n-4];
    *b = -1;
    // Initializing the values of the character array as '0'
    for(int i=6; i<n-4; i++){
        p[i]='0';
    }
}

void *mymalloc(int size){
    // Pointer points to first bookkeeping block initially
    int *a = (int*)&p[0];
    int pos = 6;
    short status = *(a+1);
    int block_size = *a;
    // Move the pointer to the consecutive blocks until a freed block with status 0 is found
    while((status==1 || block_size-6<size) && block_size!=-1){
        pos = pos+block_size+6;
        a = (int*)&p[pos-6];
        block_size = *a;
        status = *(a+1);
    }
    // If block_size==-1, the end of the array is reached, no memory is available
    if(block_size==-1){
        printf("Sorry, no memory left\n");
    }
    // Use an integer pointer to initialize the value of the bookkeeping
    if(status==0){
        *a = size;
        *(a+1) = 1;
        int *temp = (int*)&p[pos+size];
        *(temp+1) = (short)0;
        *temp = block_size-size-6;
        return &p[pos];
    }
    return NULL;
}

void cleanup(){
    int *a = (int*)&p[0];
    int pos = 6;
    short status = *(a+1);
    int block_size = *a;
    while(block_size!=-1){
        if(status==0){
            int init_pos = pos-6;
            printf("%p\n", &p[init_pos]);
            int total_free_size = 0;
            // Keep a count of sizes of consecutive free blocks to remove redundant bookkeeping blocks
            int count = 1;
            // Parses through the blocks until you find an allocated block
            while(block_size!=-1 && status==0){
                count++;
                total_free_size += block_size+6;
                pos = pos+block_size+6;
                a = (int*)&p[pos-6];
                block_size = *a;
                status = *(a+1);
                // If block size is not equal to -1, change the values of the six bytes of the bookkeeping to '0'
                if(count!=1 && block_size!=-1){
                    for(int i=pos-6; i<pos; i++){
                        p[i]='0';
                    }
                }
            }
            p[init_pos] = (int)total_free_size;
        }
        else{
            pos = pos+block_size+6;
            a = (int*)&p[pos-6];
            block_size = *a;
            status = *(a+1);
        }
    }
}

void display_mem_map(){
    // Pointer points to first bookkeeping block initially
    int *a = (int*)&p[0];
    int pos = 6;
    short status = *(a+1);
    int block_size = *a;
    // Prints initial block
    printf("0 6 book\n");
    while(block_size!=-1){
        // Prints start address and block size of allocated or free block
        printf("%d %d ", pos, block_size);
        if(status==0) printf("free\n");
        else printf("allocated\n");
        pos = pos+block_size+6;
        a = (int*)&p[pos-6];
        block_size = *a;
        status = *(a+1);
        // Prints mem_map of bookkeeping done after the block, different for final block
        if(block_size==-1) printf("%d 4 book\n", pos-6);
        else printf("%d 6 book\n",pos-6);
    }
    printf("\n");
}

void print_free_list(){
    // Pointer points to first bookkeeping block initially
    int *a = (int*)&p[0];
    int pos = 6;
    short status = *(a+1);
    int block_size = *a;
    while(block_size!=-1){
        // Prints the details of the free blocks depending on the status
        if(status==0){
            printf("%d %d\n", pos, block_size);
        }
        pos = pos+block_size+6;
        a = (int*)&p[pos-6];
        block_size = *a;
        status = *(a+1);
    }
    printf("\n");
}

void myfree(void* b){
    // Pointer points to first bookkeeping block initially
    int *a = (int*)&p[0];
    int pos = 6;
    short status = *(a+1);
    int block_size = *a;
    // Temporary pointers for storing the block_size and status of the previous block
    int *previous_block_size=malloc(sizeof(int));
    short *previous_status=malloc(sizeof(short));
    while(block_size!=-1 && (void*)&(p[pos])!=b){
        // Update the values of previous_block_size and previous_status
        *previous_block_size = block_size;
        *previous_status = status;
        pos = pos+block_size+6;
        a = (int*)&p[pos-6];
        block_size = *a;
        status = *(a+1);
    }
    int previous_block_pos = pos-*previous_block_size-12;
    // Update the value of the previous_block_size if the previous_status is 0
    if(block_size!=-1 && *previous_status==0){
        p[previous_block_pos] += block_size+6;
        cleanup();  // Cleanup blocks, removing redundant bookkeeping blocks
    }
    // If previous_block_status is 1, then just set the status of current block to 0
    else if(block_size!=-1 && *previous_status==1){
        *(a+1) = 0;
    }
}

void print_book(){
    // Pointer points to first bookkeeping block initially
    int *a = (int*)&p[0];
    int pos = 6;
    short status = *(a+1);
    int block_size = *a;
    // Set 2 variables for bookkeeping of free blocks and allocated blocks
    int free_blocks = 0;
    int allocated_blocks = 0;
    while(block_size!=-1){
        if(status) allocated_blocks+=6;
        else free_blocks+=6;
        pos = pos+block_size+6;
        a = (int*)&p[pos-6];
        block_size = *a;
        status = *(a+1);
    }
    // Print sizes of allocated blocks and free blocks bookkeeping
    printf("%d\n", allocated_blocks);
    printf("%d\n", free_blocks);
}