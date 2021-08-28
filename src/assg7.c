#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <gmp.h>

/**
 * PROBLEM: Find the solution to a congruence equation
 * APPROACH: We have ax === b (mod m), multiply by Inv(a) (assuming inverse exists) x === b * Inv(a) (mod m)
 * 
*/

int extended_euclidean(mpz_t g, mpz_t a, mpz_t b, mpz_t x, mpz_t y)
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
    mpz_set(g, old_r);

	return 0;
}

int inverse(mpz_t inv, mpz_t number, mpz_t modulo) {
	mpz_t temp, gcd;
	extended_euclidean(gcd, inv, temp, number, modulo);
	mpz_clears(temp, gcd, NULL);
}



int main(int argc, char * argv[]) {
    if (argc != 4) {
        gmp_printf("ERROR: invalid number of arguments\n");
        gmp_printf("USAGE: ./<executable> <number> <answer> <modulo>\n");
		exit(-1);
    }

    mpz_t number, multiplier, result, modulo_base, gcd, inverse, temp;
    mpz_inits(number, multiplier, result, modulo_base, gcd, inverse, temp, NULL);

	mpz_set_str(number, argv[1], 10);
	mpz_set_str(result, argv[2], 10);
	mpz_set_str(modulo_base, argv[3], 10);

	extended_euclidean(gcd, inverse, temp, number, modulo_base);

	if (mpz_cmp_ui(gcd, 1) != 0) {
		gmp_printf("No solution exists\n");
	} else {
		mpz_mul(multiplier, result, inverse);
		mpz_mod(multiplier, multiplier, modulo_base);
		gmp_printf("The solution is %Zd (mod %Zd)\n", multiplier, modulo_base);
	}

	return 0;   
}