# VectorDOT
aimed to optimize the process of vector dot product calculation

## Version_1.0
### brutal force:

```c++
    // begin time
    auto start1 = std::chrono::steady_clock::now();
    for (int i = 0; i < n; ++i) {
        result += f1[i] * f2[i];
    }
    // end time
    auto end1 = std::chrono::steady_clock::now();
```

### time cost:
We test this brutal force algorithm with two vectors each has 200 million elements and output its' calculation time.

![image-20201011203823050](C:\Users\21548\AppData\Roaming\Typora\typora-user-images\image-20201011203823050.png)

We can see that the calculation of dot product takes 1318ms, which has a lot of space to do our optimization.

## Version_2.0
To be continued...