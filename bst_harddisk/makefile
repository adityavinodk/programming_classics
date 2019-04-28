a.out: client.o bst_file.o
	gcc client.o bst_file.o
client.o: client.c bst_file.h
	gcc -c client.c bst_file.h
bst_file.o: bst_file.c bst_file.h
	gcc -c bst_file.c bst_file.h