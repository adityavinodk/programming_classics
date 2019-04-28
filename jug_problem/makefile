a.out: client.o jugs.o
	gcc client.o jugs.o
client.o: client.c jugs.h
	gcc -c client.c
jugs.o: jugs.c jugs.h
	gcc -c jugs.c