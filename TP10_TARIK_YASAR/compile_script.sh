gcc -c sorting.c -o sorting.o
gcc -c applications.c -o applications.o
gcc main.c sorting.o applications.o -o main 

