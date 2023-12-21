# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <mpfr.h>


mpfr_ptr count_pi(unsigned int start, unsigned int end, unsigned int precision){
    mpfr_ptr sum = malloc(sizeof(mpfr_ptr));

    mpfr_t n, pow_r, mul_r, div_r, sub_r, add_r;

    mpfr_inits2(
        precision, sum, n, 
        pow_r, mul_r, div_r, 
        sub_r, add_r, NULL
    );
    mpfr_set_ui(sum, 0, MPFR_RNDN);  // set sum to 0
    
    for(unsigned int i = start; i < end; i++){
        mpfr_set_ui(n, i, MPFR_RNDN);

        // 4 / (8 * n + 1)
        mpfr_mul_ui(mul_r, n, 8, MPFR_RNDN);
        mpfr_add_ui(add_r, mul_r, 1, MPFR_RNDN);
        mpfr_si_div(div_r, 4, add_r, MPFR_RNDN);
        mpfr_set(sub_r, div_r, MPFR_RNDN);

        // 2 / (8 *  n +  4)
        mpfr_mul_ui(mul_r, n, 8, MPFR_RNDN);
        mpfr_add_ui(add_r, mul_r, 4, MPFR_RNDN);
        mpfr_si_div(div_r, 2, add_r, MPFR_RNDN);
        mpfr_sub(sub_r, sub_r, div_r, MPFR_RNDN);

        //  1) / (8 *  n +  5)
        mpfr_mul_ui(mul_r, n, 8, MPFR_RNDN);
        mpfr_add_ui(add_r, mul_r, 5, MPFR_RNDN);
        mpfr_si_div(div_r, 1, add_r, MPFR_RNDN);
        mpfr_sub(sub_r, sub_r, div_r, MPFR_RNDN);

        //  1) / (8 *  n +  6)
        mpfr_mul_ui(mul_r, n, 8, MPFR_RNDN);
        mpfr_add_ui(add_r, mul_r, 6, MPFR_RNDN);
        mpfr_si_div(div_r, 1, add_r, MPFR_RNDN);
        mpfr_sub(sub_r, sub_r, div_r, MPFR_RNDN);

        mpfr_ui_pow(pow_r, 16, n, MPFR_RNDN);

        mpfr_div(div_r, sub_r, pow_r, MPFR_RNDN);

        mpfr_add(sum, sum, div_r, MPFR_RNDN);
    }
    
    mpfr_clears(
        n, pow_r, mul_r, 
        div_r, sub_r, add_r, NULL
    );

    return sum;
}


void sum_results(int precision, int n, ...) {
    va_list args;
    va_start(args, n);

    mpfr_t pi;
    mpfr_init2(pi, precision);
    mpfr_set_ui(pi, 0, MPFR_RNDN);  // set pi to 0

    for(int i = 0; i < n; i++){
        mpfr_ptr arg = va_arg(args, mpfr_ptr);
        mpfr_add(
            pi,
            pi,
            arg,
            MPFR_RNDN
        );
        mpfr_clear(arg);
    }

    // mpfr_out_str(stdout, 10, 0, pi, MPFR_RNDN);

    va_end(args);
    mpfr_clear(pi);
}
