extern char *p;

void allocate(int n); //function to allocate memory for the global array p, n number of bytes long.

void *mymalloc(int size); //function to allocate a block of size "size" from p

void myfree(void *b); //free the block pointed to by the parameter

void print_book(); // prints bytes required for allocated chunk's bookkeeping followed by bytes required for free chunk's bookkeeping on the next line. Can be the same value.
// 4  // for allocated chunk
// 10 // for free chunk

void display_mem_map();
// Assume n = 1000
// assume book keeping : 10 bytes for both allocated and free cases
//
// start_addr   block_in_bytes status
// 0		10		book
// 10           990             free
// mymalloc(100)
// 0		10		book
// 10           100             allocated
// 110		10		book
// 120          (1000 -120) = 880  free
// mymalloc(200)
// 0		10		book
// 10           100             allocated
// 110		10		book
// 120          200             allocated
// 320		10		book
// 330          670             free
// mymalloc(150)
// 0		10		book
// 10           100             allocated
// 110		10		book
// 120          200             allocated
// 320		10		book
// 330          150             allocated
// 480		10		book
// 490          510             free
// free(addr 120)
// 0		10		book
// 10           100             allocated
// 110		10		book
// 120          200             free
// 320		10		book
// 330          150             allocated
// 480		10		book
// 490          510             free