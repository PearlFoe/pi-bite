"""
Output:
    PI: 3.141592653589793
    Sum: 3.141592653388201
    Seconds: 306.94723200798035
"""
from math import pi
import time


def main():
    row_elements = 10 ** 10

    row = (
        4 / n if id_ % 2 == 0 else -4 / n
        for id_, n in enumerate(range(1, row_elements, 2))
    )

    print("PI:", pi)
    print("Sum:", sum(row))


if __name__ == '__main__':
    ts = time.time()
    main()
    print("Seconds:", time.time() - ts)
