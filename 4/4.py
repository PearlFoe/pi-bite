import os
from timeit import timeit
from ctypes import cdll, c_uint, c_int
from concurrent.futures import ProcessPoolExecutor

"""
3.py
0.5807172919994628
4.py

"""

PI_MODULE = cdll.LoadLibrary("build/libpi-bite.dylib")
PRECISION = 30_000

def _count_pi_wrapper(args) -> None:
    PI_MODULE.count_pi(*args)


def count_ranges_parallel(precision: int, workers: int = 10) -> None:
    with ProcessPoolExecutor(max_workers=workers) as executor:
        ranges = []
        range_start = 0
        for worker, range_end in enumerate(range(0, precision + precision // workers, precision // workers)):
            if range_end > range_start:
                ranges.append(
                    (c_uint(worker), c_uint(range_start), c_uint(range_end), c_uint(precision))
                )
                range_start = range_end
        executor.map(_count_pi_wrapper, ranges)


def main():
    workers = os.cpu_count()
    count_ranges_parallel(PRECISION, workers)
    PI_MODULE.sum_results(c_int(PRECISION), c_int(workers))

if __name__ == '__main__':
    print("Seconds:", timeit(main, number=1))
    print(f"Precision: {PRECISION}")
        