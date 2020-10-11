# VectorDOT
aimed to optimize the process of vector dot product calculation

## Version_1.0
### Brutal force:

```c++
    // begin time
    auto start1 = std::chrono::steady_clock::now();
    for (int i = 0; i < n; ++i) {
        result += f1[i] * f2[i];
    }
    // end time
    auto end1 = std::chrono::steady_clock::now();
```

### Time cost:
We test this brutal force algorithm with two vectors each has 200 million elements and output its' calculation time.

![image-20201011203823050](C:\Users\21548\AppData\Roaming\Typora\typora-user-images\image-20201011203823050.png)

We can see that the calculation of dot product takes 1318ms, which has a lot of space to do our optimization.

## Version_2.0
### Block vector calculation:

We use divide and conquer, partition the vector with many small block vectors with length 6, and calculate the result of dot product of the two corresponding block vectors. And then we combine each of the dot product. This way we can decrease the loop counts and arithmetic times.

```c++
float block(const float *f1, const float *f2, int i) {
    return f1[i] * f2[i] + f1[i + 1] * f2[i + 1] + f1[i + 2] * f2[i + 2] + f1[i + 3] * f2[i + 3] +
           f1[i + 4] * f2[i + 4] + f1[i + 5] * f2[i + 5];
}

	// begin time
	auto start1 = std::chrono::steady_clock::now();
    int m = n % 6;
    for (int i = 0; i < m; ++i) {
        result += f1[i] * f2[i];
    }
    for (int i = m; i < n; i += 6) {
        result += block(f1, f2, i);
    }
    // end time
    auto end1 = std::chrono::steady_clock::now();
```

### Time cost:
We test this block vector algorithm with two vectors each has 200 million elements and output its' calculation time.

![image-20201011210831497](C:\Users\21548\AppData\Roaming\Typora\typora-user-images\image-20201011210831497.png)

We can see from the screenshot that after this divide step, the time cost is reduced by half.

## Version_3.0
To be continued...