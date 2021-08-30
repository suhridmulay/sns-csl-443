#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <gmp.h>

// Once again we will use mpz_gcd to supplement our own code
// We have demonstrated gcd in Q1 and 2

int naive_euler_totient(mpz_t result, mpz_t number) {
	mpz_t i;
	mpz_init_set_ui(i, 1);

	mpz_t count;
	for(mpz_init_set_ui(count, 0); mpz_cmp(i, number) < 0; mpz_add_ui(i, i, 1)) {
		mpz_t gcd;
		mpz_init gcd;
		mpz_gcd(gcd, i, number);
		if (mpz_cmp_ui(gcd, 1) == 0) {
			mpz_add_ui(count, count, 1);
		}
	}

	mpz_set(result, count);
}

int main() {
	
}