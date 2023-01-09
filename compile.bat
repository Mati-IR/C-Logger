gcc library.c -o library.o -c
gcc main.c -o main.o -c
gcc -o myprog main.o library.o