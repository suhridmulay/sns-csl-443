# We will be using clang to compile our source
CC=clang
# Always show all warnings and treat them as errors
# As frustrating as it is, it challenges your mind
CFLAGS=-Wall -Werror
# Don't forget to link the GMP library
LFLAGS=-lgmp

main: src/main.c
	$(CC) $(CFLAGS) $(LFLAGS) src/main.c -o build/main

assignment1: src/assg1.c
	$(CC) $(CFLAGS) $(LFLAGS) src/assg1.c -o build/assg1

assignment2: src/assg2.c
	$(CC) $(CFLAGS) $(LFLAGS) src/assg2.c -o build/assg2

assignment3: src/assg3.c
	$(CC) $(CFLAGS) $(LFLAGS) src/assg3.c -o build/assg3

assignment4: src/assg4.c
	$(CC) $(CFLAGS) $(LFLAGS) src/assg4.c -o build/assg4

assignment5: src/assg5.c
	$(CC) $(CFLAGS) $(LFLAGS) src/assg5.c -o build/assg5

assignment6: src/assg6.c
	$(CC) $(CFLAGS) $(LFLAGS) src/assg6.c -o build/assg6

assignment7: src/assg7.c
	$(CC) $(CFLAGS) $(LFLAGS) src/assg7.c -o build/assg7

assignment8: src/assg8.c
	$(CC) $(CFLAGS) $(LFLAGS) src/assg8.c -o build/assg8

assignment9: src/assg9.c
	$(CC) $(CFLAGS) $(LFLAGS) src/assg9.c -o build/assg9

assignment10: src/assg10.c
	$(CC) $(CFLAGS) $(LFLAGS) src/assg10.c -o build/assg10

clean: build/*
	rm -i build/*