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

clean: build/*
	rm -i build/*