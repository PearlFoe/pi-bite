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

Actualy its impossible (or I didn't find the way) to pass pointers to child process to update value and pass it back. So I decided to
save value to file and then count sum of result from files in parent process. Its slow, but it's simple and it works.

### Build C code
```
cd 4/
conan install . --output-folder=build --build=missing
cd build/
cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build .
```

### Result 
And the result... at least 8 times slower then 3rd attempt. May be I can get rid of writing result into files using python objects writen in C, but I don'n think it will give significant speed up. So I think I will stop at this point. 

If you interested in this experiment too and have suggesions how to make if faster, feel free to open issue.

