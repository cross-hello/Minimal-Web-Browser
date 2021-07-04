main: main.o list.o get.o
	gcc -Wall main.o get.o list.o  `pkg-config --cflags gtk+-2.0` `pkg-config --libs gtk+-2.0` -o main

main.o: main.c 
	gcc -Wall main.c `pkg-config --cflags gtk+-2.0` `pkg-config --libs gtk+-2.0` -c

list.o: list.h list.c
	gcc -c list.c

get.o: get.c
	gcc -c get.c



