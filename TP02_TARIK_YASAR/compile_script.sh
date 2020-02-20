gcc -c contactlist.c -o contactlist.o
gcc -c main.c -o main.o
gcc main.c contactlist.o -o main -lm

