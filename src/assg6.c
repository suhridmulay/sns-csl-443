#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <gmp.h>

/**
 * PROBLEM: Find the multiplicative inverse on a modulo system
 * APPROACH: We already have extended euclidean algorithm
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



int main(int argc, char * argv[]) {
    if (argc != 3) {
        gmp_printf("ERROR: invalid number of arguments\n");
        gmp_printf("USAGE: ./<executable> <number> <modulo>\n");
    }

    mpz_t x, y, a, b, g;
    mpz_inits(x, y, a, b, g, NULL);
    mpz_set_str(x, argv[1], 10);
    mpz_set_str(y, argv[2], 10);

    extended_euclidean(g, a, b, x, y);
    if (mpz_cmp_ui(g, 1) != 0) {
        gmp_printf("N\n");
    } else {
		if (mpz_sgn(a) < 0) {
			mpz_add(a, a, y);
		}
        gmp_printf("Y %Zd\n", a);
    }
}