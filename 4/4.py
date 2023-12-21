import os
from timeit import timeit
from ctypes import cdll, c_uint
from concurrent.futures import ProcessPoolExecutor
    

PI_MODULE = cdll.LoadLibrary("build/libpi-bite.dylib")
PRECISION = 100

def count_ranges_parallel(precision: int, workers: int = 10) -> tuple:
    with ProcessPoolExecutor(max_workers=workers) as executor:
        ranges = []
        range_start = 0
        for range_end in range(0, precision, precision // workers):
            if range_end > range_start:
                ranges.append(
                    (c_uint(range_start), c_uint(range_end), c_uint(precision))
                )
                range_start = range_end

        return executor.map(PI_MODULE.count_pi, ranges)


def main():
    workers = os.cpu_count()
    results = count_ranges_parallel(
        precision=PRECISION,
        workers=workers,
    )
    PI_MODULE.sum_results(c_uint(PRECISION), c_uint(workers), *results)

if __name__ == '__main__':
    print("Seconds:", timeit(main, number=1))