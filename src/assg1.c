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

	// Allocate storage for numbers
	mpz_t * nums = malloc(sizeof(mpz_t) * argc);
	int number_of_numbers = 0;

	

	for (int i = 1; i < argc; i++) {
		mpz_init_set_str(nums[number_of_numbers], argv[i], 10);
		number_of_numbers += 1;
	}

	// Store the GCD in this variable
	mpz_t g;
	mpz_init(g);
	mpz_set(g, nums[0]);

	for (int i = 1; i < number_of_numbers; i++) {
		mpz_custom_gcd(g, nums[i], g);
	}

	gmp_printf("%Zd\n", g);
	

	return 0;
}