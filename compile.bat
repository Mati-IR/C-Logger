gcc timestamp.c -o timestamp.o -c
gcc library.c -o library.o -c
gcc main.c -o main.o -c
gcc -o myprog main.o library.o timestamp.o

rm *.o
