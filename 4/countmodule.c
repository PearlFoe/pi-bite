# define PY_SSIZE_T_CLEAN
# include <Python.h>

# include <mpfr.h>


void count_pi(unsigned int start, unsigned int end, unsigned int precision){
    mpfr_t sum, n;
    mpfr_t pow_r, mul_r, div_r, sub_r, add_r;

    mpfr_inits2(
        precision, sum, n, 
        pow_r, mul_r, div_r, 
        sub_r, add_r, NULL
    );
    mpfr_set_ui(sum, 0, MPFR_RNDN);  // set sum to 0
    
    for(u_int32_t i = start; i < end; i++){
        mpfr_set_ui(n, i, MPFR_RNDN);

        // mpz(4) / (mpz(8) * mpz(n) + mpz(1))
        mpfr_mul_ui(mul_r, n, 8, MPFR_RNDN);
        mpfr_add_ui(add_r, mul_r, 1, MPFR_RNDN);
        mpfr_si_div(div_r, 4, add_r, MPFR_RNDN);
        mpfr_set(sub_r, div_r, MPFR_RNDN);

        // mpz(2) / (mpz(8) * mpz(n) + mpz(4))
        mpfr_mul_ui(mul_r, n, 8, MPFR_RNDN);
        mpfr_add_ui(add_r, mul_r, 4, MPFR_RNDN);
        mpfr_si_div(div_r, 2, add_r, MPFR_RNDN);
        mpfr_sub(sub_r, sub_r, div_r, MPFR_RNDN);

        // mpz(1) / (mpz(8) * mpz(n) + mpz(5))
        mpfr_mul_ui(mul_r, n, 8, MPFR_RNDN);
        mpfr_add_ui(add_r, mul_r, 5, MPFR_RNDN);
        mpfr_si_div(div_r, 1, add_r, MPFR_RNDN);
        mpfr_sub(sub_r, sub_r, div_r, MPFR_RNDN);

        // mpz(1) / (mpz(8) * mpz(n) + mpz(6))
        mpfr_mul_ui(mul_r, n, 8, MPFR_RNDN);
        mpfr_add_ui(add_r, mul_r, 6, MPFR_RNDN);
        mpfr_si_div(div_r, 1, add_r, MPFR_RNDN);
        mpfr_sub(sub_r, sub_r, div_r, MPFR_RNDN);

        // () / mpz(16) ** mpz(n)
        mpfr_ui_pow(pow_r, 16, n, MPFR_RNDN);
        mpfr_div(div_r, sub_r, pow_r, MPFR_RNDN);

        mpfr_add(sum, sum, div_r, MPFR_RNDN);
    }

    //mpfr_out_str(stdout, 10, 0, sum, MPFR_RNDN);
}


void test() {
    mpfr_t x;
    mpfr_t y;
    mpfr_t sum;

    mpfr_inits2(20, x, y, sum, NULL);

    mpfr_set_si(x, 99999, MPFR_RNDN);
    mpfr_set_si(y, 99998, MPFR_RNDN);

    mpfr_add(sum, x, y, MPFR_RNDN);

    mpfr_out_str(stdout, 10, 0, sum, MPFR_RNDN);
}

