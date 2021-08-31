#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <gmp.h>

// Once again we will use mpz_gcd to supplement our own code
// We have demonstrated gcd in Q1 and 2
/**
 * @param result result of operation
 * @param number number to calculate phi(z) of
*/
int naive_euler_totient(mpz_t result, mpz_t number) {
	mpz_t i;
	mpz_init_set_ui(i, 1);

	mpz_t count;
	for(mpz_init_set_ui(count, 0); mpz_cmp(i, number) < 0; mpz_add_ui(i, i, 1)) {
		mpz_t gcd;
		mpz_init(gcd);
		mpz_gcd(gcd, i, number);
		if (mpz_cmp_ui(gcd, 1) == 0) {
			mpz_add_ui(count, count, 1);
		}
	}

	mpz_set(result, count);
	return 0;
}

int order_under_modulus(mpz_t result, mpz_t number, mpz_t modulo) {
	mpz_t power;
	mpz_init_set_ui(power, 0);
	
	mpz_t num;
	mpz_init_set(num, number);

	do {
		// y = y * x
		mpz_mul(num, num, number);
		// pow = pow + 1
		mpz_add_ui(power, power, 1);
		// y = y % n
		mpz_mod(num, num, modulo);
	} while (mpz_cmp(num, number) != 0);

	mpz_set(result, power);
	return 0;
}

int main(int argc, char *argv[]) {
	mpz_t number;
	if (argc != 2) {
		gmp_fprintf(stderr, "ERROR: %s\n", "invalid number of arguments");
		gmp_fprintf(stderr, "USAGE: ./<executable> <number>\n");
		exit(-1);
	}

	mpz_init_set_str(number, argv[1], 10);

	// Calculate the totient, and totient of totient
	// totient of totient is the number of primitive roots
	mpz_t totient, totient_of_totient;
	mpz_inits(totient, totient_of_totient, NULL);
	naive_euler_totient(totient, number);
	naive_euler_totient(totient_of_totient, totient);
	gmp_printf("Total number of primitive roots: %Zd\n", totient_of_totient);

	// Iterate to find the first primitive root
	mpz_t first_primitive_root, iterator;
	mpz_init(first_primitive_root);
	mpz_init_set_ui(iterator, 1);
	for (; mpz_cmp(iterator, number) < 0; mpz_add_ui(iterator, iterator, 1)) {
		mpz_t order;
		mpz_init(order);
		order_under_modulus(order, iterator, number);
		gmp_printf("Order of %Zd under modulus %Zd = %Zd\n", iterator, number, order);
		if (mpz_cmp(order, totient) == 0) {
			// We have found the first primitive root
			mpz_set(first_primitive_root, iterator);
			gmp_printf("First Primitive Root: %Zd\n", first_primitive_root);
			break;
		}
	}

	// Use this root to generate others
	mpz_t generator;
	mpz_init_set(generator, first_primitive_root);
	mpz_set_ui(iterator, 1);
	// One root to generate them all
	// Where power is coprime to the totients
	for (; mpz_cmp(iterator, totient) < 0; mpz_add_ui(iterator, iterator, 1)) {
		mpz_t gcd_totient_power;
		mpz_gcd(gcd_totient_power, totient, iterator);

		if (mpz_cmp_ui(gcd_totient_power, 1) == 0) {
			
			gmp_printf("Primitive Root: %Zd\n", generator);
		}

		mpz_mul(generator, generator, first_primitive_root);
		mpz_mod(generator, generator, number);
	}
}