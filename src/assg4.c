#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <gmp.h>

#define mpz_increment(VAR, STEP) mpz_add_ui(VAR, VAR, STEP)

/**
 * PROBLEM: given a set of integers output the reduced residue system modulo m
 * APPROACH: 1. brute force?
*/

// We already have GCD code for problem 1
// No need to redo or redemonstrate
// We can use mpz_gcd

int main(int argc, char *argv[]) {
    if (argc != 2) {
        gmp_printf("ERROR: invalid number of arguments\n");
        gmp_printf("USAGE: ./<executable> <number>\n");
        exit(-1);
    }

    // Read and store the number the user entered
    mpz_t number;
    mpz_init_set_str(number, argv[1], 10);

    // Store number of numbers;
    mpz_t number_of_numbers;
    mpz_init_set_ui(number_of_numbers, 0);

    // Brute force iteration
    mpz_t iterator;
    for(mpz_init_set_ui(iterator, 1); mpz_cmp(iterator, number) < 0; mpz_increment(iterator, 1)) {
        mpz_t g;
        mpz_init(g);
        mpz_gcd(g, iterator, number);
        if (mpz_cmp_ui(g, 1) == 0) {
            gmp_printf(" %Zd (modulo %Zd)\n", iterator, number);
            mpz_increment(number_of_numbers, 1);
        }
    }
    gmp_printf("Found %Zd numbers\n", number_of_numbers);
    return 0;
}