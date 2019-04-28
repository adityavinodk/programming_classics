a.out : client.o bin_counter.o
	gcc client.o bin_counter.o
client.o : client.c bin_counter.h
	gcc -c client.c
bin_counter.o : bin_counter.c bin_counter.h
	gcc -c bin_counter.c