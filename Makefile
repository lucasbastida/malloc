malloc: main.o malloc.o
	gcc $(CFLAGS) -o malloc main.o malloc.o

malloc.o: ./source/malloc.c ./source/malloc.h
	gcc $(CFLAGS) -c ./source/malloc.c

main.o: ./source/main.c ./source/malloc.h
	gcc $(CFLAGS) -c ./source/main.c

clean:
	rm -f *.o malloc