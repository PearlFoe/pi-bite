"""
Output:
    Precision: 18263
    Seconds: 67.09231305122375
"""
from timeit import timeit

import gmpy2
from gmpy2 import mpq, mpz

def main():
    series_elements = 10 ** 5
    
    gmpy2.set_context(gmpy2.context())
    gmpy2.get_context().precision = series_elements

    series = (
        (
        mpz(4) / (mpz(8) * mpz(n) + mpz(1)) - 
        mpz(2) / (mpz(8) * mpz(n) + mpz(4)) - 
        mpz(1) / (mpz(8) * mpz(n) + mpz(5)) - 
        mpz(1) / (mpz(8) * mpz(n) + mpz(6))
        ) / mpz(16) ** mpz(n)
        for n in range(series_elements)
    )
    print(f"Precision: {len(str(sum(series))) - 2}") # not to count 3.

if __name__ == '__main__':
    print("Seconds:", timeit(main, number=1))
