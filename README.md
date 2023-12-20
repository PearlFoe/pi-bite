# pi-bite
I was interested, how many digits of the Pi number I can count... Let's see

**All tests were done on macbook pro m1 (CPU: 10 cores, RAM: 16 GB)**

## Attempt 1
I've used [Gregory's series](https://en.wikipedia.org/wiki/Gregory%27s_series) to check how many digits I can get in about 5 minutes.
```
PI: 3.141592653589793
Sum: 3.141592653388201
Seconds: 306.94723200798035

Result: 9 digits
```

## Attempt 2
Tried to use better formula([BBP](https://en.wikipedia.org/wiki/Bailey%E2%80%93Borwein%E2%80%93Plouffe_formula)) to optimize code and [gmpy2](https://gmpy2.readthedocs.io/en/latest/intro.html) for highly accurate floating-point arithmetic.


```
Precision: 30102
Seconds: 67.09231305122375
```

## Attempt 3
Made parallel processing using [concurrent.futures.ProcessPoolExecutor](https://docs.python.org/3/library/concurrent.futures.html#processpoolexecutor)

```
Precision: 301030
Seconds: 1651.0571850829947
```

## Attempt 4
Rewrote counting logic in C using [MPFR](https://www.mpfr.org/mpfr-current/mpfr.html). Still use [BBP formula](https://en.wikipedia.org/wiki/Bailey%E2%80%93Borwein%E2%80%93Plouffe_formula).

### Build C code
```
cd 4/
conan install . --output-folder=build --build=missing
cd build/
cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build .
```

### Result (intermediate)
Got 2.5 speed up in single-threaded run (30k precision = 26 sec).

TODO: make it parallel.