#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <gmp.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        gmp_fprintf(stderr, "ERROR: Invalid number of arguments\n");
        gmp_fprintf(stderr, "USAGE: ./<executable> <number> <modulo>\n");
        exit(-1);
    }

    mpz_t iterator, number, modulo_base, mod, power;
    mpz_init_set_str(number, argv[1], 10);
    mpz_init_set_str(modulo_base, argv[2], 10);
    mpz_init_set(iterator, number);
    mpz_init(mod);
    mpz_init_set_ui(power, 1);

    do {
        if (mpz_cmp_ui(iterator, 1) == 0) {
            gmp_printf("Y %Zd\n", power);
            exit(0);
        }
        mpz_mul(iterator, iterator, number);
        mpz_add_ui(power, power, 1);
        mpz_mod(iterator, iterator, modulo_base);
    } while (mpz_cmp(iterator, number) != 0);

    gmp_printf("N\n");
}