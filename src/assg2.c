#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <gmp.h>

// This is basically a 1-to-1 copy of wikipedia article's descrption of the algorithm
// A copy can be found here: https://en.wikipedia.org/wiki/Extended_Euclidean_algorithm
// The compiler will optimise all the unused vars and everything no need to worry
// IMPORTANT: mpz_inits takes NULL terminated list of arguments
int extended_euclidean(mpz_t a, mpz_t b, mpz_t x, mpz_t y)
{
	mpz_t old_r, r;
	mpz_init(old_r);
	mpz_init(r);
	mpz_set(old_r, x);
	mpz_set(r, y);

	mpz_t old_s, s;
	mpz_init_set_str(old_s, "1", 10);
	mpz_init_set_str(s, "0", 10);

	mpz_t old_t, t;
	mpz_init_set_str(old_t, "0", 10);
	mpz_init_set_str(t, "1", 10);

	while (mpz_sgn(r) != 0)
	{

		mpz_t quotient;
		mpz_init(quotient);
		mpz_div(quotient, old_r, r);

		// (old_r, r) = (r, old_r - r * quot)
		{
			mpz_t temp_r, temp_r_times_quotient;
			mpz_inits(temp_r, temp_r_times_quotient, NULL);
			mpz_set(temp_r, r);
			mpz_set_str(temp_r_times_quotient, "0", 10);
			mpz_mul(temp_r_times_quotient, temp_r, quotient);
			mpz_sub(r, old_r, temp_r_times_quotient);
			mpz_set(old_r, temp_r);
		}

		// (old_s, s) = (s, old_s - s * quot)
		{
			mpz_t temp_s, temp_s_times_quotient;
			mpz_inits(temp_s, temp_s_times_quotient, NULL);
			mpz_set(temp_s, s);
			mpz_set_str(temp_s_times_quotient, "0", 10);
			mpz_mul(temp_s_times_quotient, temp_s, quotient);
			mpz_sub(s, old_s, temp_s_times_quotient);
			mpz_set(old_s, temp_s);
		}

		// (old_t, t) = (t, old_t - t * quot)
		{
			mpz_t temp_t, temp_t_times_quotient;
			mpz_inits(temp_t, temp_t_times_quotient, NULL);
			mpz_set_str(temp_t_times_quotient, "0", 10);
			mpz_set(temp_t, t);
			mpz_mul(temp_t_times_quotient, temp_t, quotient);
			mpz_sub(t, old_t, temp_t_times_quotient);
			mpz_set(old_t, temp_t);
		}
	}

	mpz_set(a, old_s);
	mpz_set(b, old_t);

	return 0;
}

int main(int argc, char *argv[])
{

	// Allocate storage for numbers
	// mpz_t *nums = malloc(sizeof(mpz_t) * argc);
	// int number_of_numbers = 0;

	mpz_t x, y;
	mpz_init(x);
	mpz_init(y);

	mpz_set_str(x, argv[1], 10);
	mpz_set_str(y, argv[2], 10);

	// Read the numbers from argc
	/*
	for (int i = 1; i < argc; i++)
	{
		mpz_init_set_str(nums[number_of_numbers], argv[i], 10);
		number_of_numbers += 1;
	}
	*/

	mpz_t a, b;
	mpz_init(a);
	mpz_init(b);

	extended_euclidean(a, b, x, y);
	gmp_printf("Coefficients are: %Zd and %Zd\n", a, b);
}