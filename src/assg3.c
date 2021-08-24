#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <gmp.h>


int pf(mpz_t number) {
	mpz_t num, factor, root_n, remainder;
    mpz_inits(num, factor, root_n, remainder, NULL);
    mpz_set(num, number);
    mpz_set_ui(factor, 2);

    // Extract all 2s from the factorisation
    mpz_mod(remainder, num, factor);
    while (mpz_cmp_ui(remainder, 0) == 0)
    {
        gmp_printf("Factor: %Zd\n", factor);
        mpz_divexact(num, num, factor);
        mpz_mod(remainder, num, factor);
    }
    mpz_sqrt(root_n, num);
    mpz_set_ui(factor, 3);
    // Iterate through numbers searching for factors
    for (; mpz_cmp(factor, root_n) <= 0; mpz_add_ui(factor, factor, 2))
    {
        mpz_mod(remainder, num, factor);
        // Whenever a factor is found
        // Extract all its ocurrences
        while (mpz_cmp_ui(remainder, 0) == 0)
        {
            gmp_printf("Factor: %Zd\n", factor);
            mpz_divexact(num, num, factor);
            mpz_sqrt(root_n, num);
            mpz_mod(remainder, num, factor);
        }
    }
    // If we still have someething left, it will be the largest prime factor
    // Which is a complement of the ones we found earlier
    if (mpz_cmp_ui(num, 2) > 0)
    {
        gmp_printf("Factor: %Zd", num);
    }
    return 0;
}

int main(int argc, char *argv[]) {
	mpz_t number;
	mpz_t nfacs;

	mpz_inits(number, nfacs, NULL);

	if (argc != 2) {
		fprintf(stderr, "%s\n", "USAGE: use with one argument ie number to factorise.\nEG: ./<executable> <number-to-factorise> ");
		exit(-1);
	}

	mpz_set_str(number, argv[1], 10);
	pf(number);
	gmp_printf("\n");
	return 0;
}