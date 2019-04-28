a.out : client.o my_malloc.o
	gcc client.o my_malloc.o
client.o : client.c my_malloc.h
	gcc -c client.c
my_malloc.o : my_malloc.c my_malloc.h
	gcc -c my_malloc.c