# Segment Tree
An implementation of a segment tree for finding minimum and maximum values in C.

![Segment Tree Path](https://en.algorithmica.org/hpc/data-structures/img/segtree-path.png)

### Functionality
Users input numbers separated by spaces and can query for the minimum or maximum within a specified interval.
- Example: 'm 1 5' retrieves the minimum value from the interval 2 to 6.
- Example: 'M 0 24' retrieves the maximum value from the interval 1 to 25.

### Time complexity
- The time complexity for building the segment tree is O(n), as each node is visited once.
- The time complexity for querying the minimum or maximum value within a specified interval is O(log n), as the tree is traversed in a logarithmic manner.

### Test Files
The test files consist of valid inputs, with each query within the bounds of the input numbers.
- Numbers fall within the range <img src="https://latex.codecogs.com/svg.image?x\in%20\left\(%200,10000\right\)">
- Number of elements per test: <img src="https://latex.codecogs.com/svg.image?n\in%20\left\{%2010,100,1000,10000,100000\right\}" title="n\in \left\{% 10,100,1000,10000,100000\right\}" />
- Number of queries per test: <img src="https://latex.codecogs.com/svg.image?\frac{n}{2}%20\cdot%20\log_{10}(n)" title="\frac{n}{2} \cdot \log_{10}(n)" />

### Test script
The test script runs all test files in the tests directory and reports on the success or failure of each test. Additionally, it runs all test files in the tests directory with valgrind, to check for memory leaks.

### Time complexity benchmark
The following table shows the time taken to run each test.
| Test File | Real Time | User Time | Sys Time | Elements | Queries |
| --- | --- | --- | --- | --- | --- |
| 0 | 0.006s | 0.002s | 0.000s | 10     | 10     |
| 1 | 0.007s | 0.002s | 0.000s | 100    | 200    |
| 3 | 0.009s | 0.003s | 0.001s | 1000   | 3000   |
| 3 | 0.042s | 0.023s | 0.001s | 10000  | 40000  |
| 4 | 0.513s | 0.312s | 0.011s | 100000 | 500000 |

The times were recorded by running with the following optimization: `-Ofast`.
