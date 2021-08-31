#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include <gmp.h>

#define DEBUG_MODE (1 == 1)

/**
 * Uses extended euclidean algorithm to calculate coefficients and gcd
 * @param g stores gcd of given numbers
 * @param a stores first extended euclidean coefficient
 * @param b stores second extended euclidean coefficient
 * @param x extended eucliden first number
 * @param y extended euclidean algorithm input second number
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
    mpz_t temp, gcd, tnum;
    mpz_inits(temp, gcd, tnum, NULL);
    mpz_mod(tnum, number, modulo);
    extended_euclidean(gcd, inv, temp, tnum, modulo);
    mpz_mod(inv, inv, modulo);
    mpz_clears(temp, gcd, NULL);
    return 0;
}

// Reference: https://en.wikipedia.org/wiki/Chinese_remainder_theorem#Existence_(direct_construction)
int crt(mpz_t res, int N, mpz_t * as, mpz_t * bs, mpz_t * ns) {
    // Our equations are in ai * x === bi (mod ni) form
    // Let's reduce all equations to x === ci (mod ni) form
    mpz_t * cs = (mpz_t *) malloc(sizeof(mpz_t) * N);
    for (int i = 0; i < N; i++) {
        mpz_t ai_inv;
        mpz_init(ai_inv);
        inverse(ai_inv, as[i], ns[i]);
        mpz_init(cs[i]);
        mpz_mul(cs[i], bs[i], ai_inv);
        mpz_mod(cs[i], cs[i], ns[i]);
    }

    
    if (DEBUG_MODE) {
        gmp_printf("Reduced equations: \n");
        for (int i = 0; i < N; i++) {
            gmp_printf("x === %Zd (mod %Zd)\n", cs[i], ns[i]);
        }
    }
    

    // Next now we calculate Ni which is product of all ns except ni
    mpz_t product_of_ns;
    mpz_init_set_ui(product_of_ns, 1);
    for (int i = 0; i < N; i++) {
        mpz_mul(product_of_ns, product_of_ns, ns[i]);
    }

    // Product of all except ith is N
    mpz_t * products_of_all_except_ith = malloc(sizeof(mpz_t) * N);
    for (int i = 0; i < N; i++) {
        mpz_init(products_of_all_except_ith[i]);
        mpz_divexact(products_of_all_except_ith[i], product_of_ns, ns[i]);
    }
    
    // Step 3, calculate Mi, which is the multiplicative inverse of Ni modulo ni
    mpz_t * Ms = (mpz_t *) malloc(sizeof(mpz_t) * N);
    for (int i = 0; i < N; i++) {
        mpz_init(Ms[i]);
        inverse(Ms[i], products_of_all_except_ith[i], ns[i]);
        mpz_mod(Ms[i], Ms[i], ns[i]);
    }

    /**
     * Now on to the final result
     * The result is expressed as 
     * SUMMATION from i = 0 .. N (cs[i] * Ms[i] * Ns[i])
     * */
    mpz_t result;
    mpz_init_set_ui(result, 0);

    for (int i = 0; i < N; i++) {
        mpz_t temp;
        mpz_init_set_ui(temp, 1);
        mpz_mul(temp, temp, cs[i]);
        mpz_mul(temp, temp, Ms[i]);
        mpz_mul(temp, temp, products_of_all_except_ith[i]);
        mpz_add(result, result, temp);
        mpz_clear(temp);
    }

    mpz_mod(result, result, product_of_ns);
    
    if (DEBUG_MODE) {
        gmp_printf("%Zd (mod %Zd)\n", result, product_of_ns);
    }
    
    mpz_set(res, result);
    return 0;
}

int main(int argc, char *argv[]) {

    if (argc < 2) {
        gmp_fprintf(stderr, "ERROR: insufficient arguments\n");
        gmp_fprintf(stderr, "USAGE: ./<executable> <number-of-congruences> <a-1> <b-1> <n-1> <a-2> <b-2> <n-2> ...");
    }

    int N;
    N = atoi(argv[1]);

    mpz_t *as, *bs, *ns;
    as = (mpz_t *) malloc(sizeof(mpz_t) * N);
    bs = (mpz_t *) malloc(sizeof(mpz_t) * N);
    ns = (mpz_t *) malloc(sizeof(mpz_t) * N);

    // Check whether we have at least the required number of arguments
    if (argc < 1 + 1  + 3 * N) {
        gmp_fprintf(stderr, "ERROR: insufficient arguments\n");
        gmp_fprintf(stderr, "USAGE: ./<executable> <number-of-congruences> <a-1> <b-1> <n-1> <a-2> <b-2> <n-2> ...");
    }

    for (int i = 0; i < N; i++) {
        mpz_inits(as[i], bs[i], ns[i], NULL);
        mpz_set_str(as[i], argv[3 * i + 2], 10);
        mpz_set_str(bs[i], argv[3 * i + 3], 10);
        mpz_set_str(ns[i], argv[3 * i + 4], 10);

        // Check whether n and a are coprime
        mpz_t g;
        mpz_init(g);
        mpz_gcd(g, as[i], ns[i]);
        if (mpz_cmp_ui(g, 1) != 0) {
            gmp_printf("N\n");
            exit(-1);
        }

        // Check whether b is less than n
        if (mpz_cmp(bs[i], ns[i]) > 0) {
            gmp_printf("N\n");
            exit(-1);
        }
    }

    // Check for pairwise coprime
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            mpz_t g;
            mpz_init(g);
            mpz_gcd(g, ns[i], ns[j]);
            if (mpz_cmp_ui(g, 1) != 0) {
                gmp_printf("N\n");
                exit(-1);
            }
        }
    }

    

    if (DEBUG_MODE) {
        for (int i = 0; i < N; i++) {
            gmp_printf("Equation %d: %Zd * x === %Zd (mod %Zd)\n", i + 1, as[i], bs[i], ns[i]);
        }
    }
    
    mpz_t result;
    crt(result, N, as, bs, ns);

    return 0;
}