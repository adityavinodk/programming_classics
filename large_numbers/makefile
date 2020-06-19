a.out: client.o bignum.o
	gcc client.o bignum.o
client.o: client.c bignum.h
	gcc -c client.c bignum.h
bignum.o: bignum.c bignum.h
	gcc -c bignum.c bignum.h
clean:
	rm client.o a.out bignum.o bignum.h.gch
