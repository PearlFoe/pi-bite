# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <string.h>
# include <mpfr.h>


const char * DELIMETER = "===";


void write_result(mpfr_ptr result, unsigned int worker){
    char * file_name[50];
    snprintf(file_name, sizeof(file_name), "%d.txt", worker);
    FILE * file_ptr = fopen(file_name, "w");

    mpfr_exp_t exp_t = 0;


    char * result_str = mpfr_get_str(NULL, &exp_t, 10, 0, result, MPFR_RNDN);

    char * exp_str[10];
    sprintf(exp_str, "%ld", exp_t);

    fwrite(result_str, sizeof(char), strlen(result_str), file_ptr);  // save number
    fwrite(DELIMETER, sizeof(char), strlen(DELIMETER), file_ptr);  // save delimeter
    fwrite(exp_str, sizeof(char), strlen(exp_str), file_ptr);  // save exponent

    fclose(file_ptr);
}


mpfr_ptr read_result(int worker, int precision){
    char * file_name[50];
    snprintf(file_name, sizeof(file_name), "%d.txt", worker);

    FILE * file_ptr = fopen(file_name, "r");


    char * file_content[precision];
    char * result_str;
    char * exp_str;

    fread(file_content, sizeof(char), sizeof(file_content), file_ptr);

    result_str = strtok(file_content, DELIMETER);
    exp_str = strtok(NULL, DELIMETER);

    mpfr_exp_t exp_t = atol(exp_str);

    mpfr_ptr result = malloc(sizeof(mpfr_t));
    mpfr_init2(result, precision);
    mpfr_set_str(result, result_str, 10, MPFR_RNDN);
    mpfr_pow_si(result, result, exp_t, MPFR_RNDN);

    fclose(file_ptr);
    return result;
}


void count_pi(unsigned int worker, int start, unsigned int end, unsigned int precision){
    mpfr_t sum, n, pow_r, mul_r, div_r, sub_r, add_r;

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

    write_result(sum, worker);

    mpfr_clears(
        sum, n, pow_r, mul_r, 
        div_r, sub_r, add_r, NULL
    );
}


void sum_results(int precision, int workers) {
    mpfr_t pi;
    mpfr_init2(pi, precision);
    mpfr_set_ui(pi, 0, MPFR_RNDN);  // set pi to 0

    for(int worker = 1; worker < workers; worker++){
        mpfr_ptr arg = read_result(worker, precision);

        mpfr_add(
            pi,
            pi,
            arg,
            MPFR_RNDN
        );
        mpfr_clear(arg);
    }


    mpfr_exp_t exp_t = 0;
    char * pi_str = mpfr_get_str(NULL, &exp_t, 10, 0, pi, MPFR_RNDN);

    // printf("PI: \n");
    // mpfr_out_str(stdout, 10, 0, pi, MPFR_RNDN);
    printf("Len: %d\n", strlen(pi_str)-2);
    mpfr_clear(pi);
}
