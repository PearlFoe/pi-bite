from timeit import timeit
from ctypes import cdll, util, c_uint
from concurrent.futures import ProcessPoolExecutor
    
from gmpy2 import mpfr


# count_module = cdll.LoadLibrary(util.find_library("pi-bite"))
count_module = cdll.LoadLibrary("build/libpi-bite.dylib")



def main():
    count_module.count_pi(c_uint(0), c_uint(30_000), c_uint(30_000))
    

if __name__ == '__main__':
    print("Seconds:", timeit(main, number=1))