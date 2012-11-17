all:		term

term:		main.o
	gcc -o term main.o


main.o:		main.c header.h
	gcc -c main.c -Wall

clean:
	rm *.o term
