#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <gmp.h>

int mpz_custom_gcd(mpz_t result, mpz_t a, mpz_t b) {
	// Create store to store our gcd
	mpz_t g;
	mpz_init(g);

	// Store the result of modulo in g
	mpz_mod(g, a, b);

	// Euclid's algorithm
	// Check whether the gcd is 0
	if (mpz_sgn(g) == 0) {
		// If yes, we have found our gcd return to the user
		mpz_set(result, b);
	} else {
		// Otherwise calculate gcd = gcd of remainder and the smaller operand
		mpz_custom_gcd(result, b, g);
	}

	return 0;
}

int main(int argc, char *argv[]) {
	mpz_t a;
	mpz_init_set_str(a, "19286381725368512397612", 10);

	mpz_t b;
	mpz_init_set_str(b, "144", 10);

	mpz_t g;
	mpz_init(g);

	mpz_custom_gcd(g, a, b);

	gmp_printf("gcd = %Zd\n", g);

	return 0;
}