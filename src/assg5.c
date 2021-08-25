#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <gmp.h>

int fermats_little_theorem(mpz_t number, mpz_t power, mpz_t modulo) {
    int steps = 0;

    mpz_t start;
    mpz_init_set_ui(start, 1);

    mpz_t exponent;
    mpz_init_set(exponent, number);
    mpz_mod(exponent, exponent, modulo);

    int size = mpz_sizeinbase(power, 2);

    for (int i = 0; i < size; i++) {
        int bit = mpz_tstbit(power, i);
        gmp_printf("bit at position %d of \'power\' is %d\n", i, bit);

        if (bit == 1) {
            gmp_printf("Since bit is 1 we incorporate the exponent (%Zd) into final result\n", exponent);
            gmp_printf("%Zd * %Zd = ", start, exponent);
            mpz_mul(start, start, exponent);
            mpz_mod(start, start, modulo);
            gmp_printf("%Zd (mod %Zd)\n", start, modulo);
        }

        mpz_mul(exponent, exponent, exponent);
        mpz_mod(exponent, exponent, modulo);
        gmp_printf("new exponent = %Zd (mod %Zd)\n", exponent, modulo);
    }

    gmp_printf("%Zd pow %Zd = %Zd (modulo %Zd)\n", number, power, start, modulo);
    return steps;
}

int main(int argc, char * argv[]) {
    if (argc != 4) {
        gmp_fprintf(stderr, "ERROR: %s\n", "Invalid number of arguments\n");
        gmp_fprintf(stderr, "USAGE: ./<executable> <number> <power> <modulo>\n");
        exit(-1);
    }

    // Init storage for number, power and modulo
    mpz_t number, power, modulo;
    mpz_inits(number, power, modulo, NULL);

    // Read input from the user
    mpz_set_str(number, argv[1], 10);
    mpz_set_str(power, argv[2], 10);
    mpz_set_str(modulo, argv[3], 10);

    fermats_little_theorem(number, power, modulo);
}