"""
Output:
    Precision: 301030
    Seconds: 1651.0571850829947
"""
from timeit import timeit
from concurrent.futures import ProcessPoolExecutor

import gmpy2
from gmpy2 import mpq, mpz, mpfr


def count_series_sum(args: tuple[int, int, int]) -> mpfr:
    start, end, precision = args
    with gmpy2.get_context() as context:
        context.precision = precision
        
        return sum(
            (mpz(4) / (mpz(8) * mpz(n) + mpz(1)) - 
            mpz(2) / (mpz(8) * mpz(n) + mpz(4)) - 
            mpz(1) / (mpz(8) * mpz(n) + mpz(5)) - 
            mpz(1) / (mpz(8) * mpz(n) + mpz(6))
            ) / mpz(16) ** mpz(n)
            for n in range(start, end)
        )


def count_pi(precision: int, series_elements: int) -> mpfr:
    workers = 10
    with ProcessPoolExecutor(max_workers=workers) as executor:
        ranges = []
        range_start = 0
        for range_end in range(0, series_elements, series_elements // workers):
            if range_end > range_start:
                ranges.append(
                    (range_start, range_end, precision)
                )
                range_start = range_end

        return sum(executor.map(count_series_sum, ranges))


def main():
    precision = series_elements = 10 ** 6
    
    gmpy2.set_context(gmpy2.context())
    gmpy2.get_context().precision = precision
    

    pi = count_pi(precision, series_elements)
    print(f"Precision: {len(str(pi)) - 2}") # not to count 3.
    
    

if __name__ == '__main__':
    print("Seconds:", timeit(main, number=1))
