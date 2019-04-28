#include <stdio.h>
#include "my_malloc.h"

int main(){
    allocate(1000);
    void *a = mymalloc(50);
    display_mem_map();
    void *b = mymalloc(100);
    display_mem_map();
    // print_free_list();
    myfree(b);
    // print_free_list();
    display_mem_map();
    void *c = mymalloc(60);
    display_mem_map();
    void *d = mymalloc(20);
    display_mem_map();
    myfree(c);
    // print_free_list();
    display_mem_map();
    // printf("pointer being freed - d\n");
    // myfree(d);
    // display_mem_map();  
    // print_free_list();
    print_book();
}       