CFLAGS=-Wall -Wextra -std=c11 -pedantic

main:tree.h main.c
	clang -o main $(CFLAGS) main.c
