# We will be using clang to compile our source
CC=clang
# Always show all warnings and treat them as errors
# As frustrating as it is, it challenges your mind
CFLAGS=-Wall -Werror
# Don't forget to link the GMP library
LFLAGS=-lgmp

main: src/main.c
	$(CC) $(CFLAGS) $(LFLAGS) src/main.c -o build/main

clean: build/*
	rm -i build/*