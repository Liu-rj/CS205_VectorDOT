#include <iostream>
#include <chrono>
#include <random>

using namespace std;

int main() {
    int n = 200000000;
    random_device r;
    default_random_engine e(r());
    uniform_real_distribution<float> uniform_dist(-1000000000, 1000000000);
    auto *f1 = new float[n];
    auto *f2 = new float[n];
    float result = 0;

    cout << "(exit with #)" << endl << "Please input your vector's length:" << endl << "Please input the first vector:" << endl;
    for (int i = 0; i < n; ++i) {
        f1[i] = uniform_dist(e);
    }

    cout << "Please input the second vector:" << endl;
    for (int i = 0; i < n; ++i) {
        f2[i] = uniform_dist(e);
    }

    // begin time
    auto start1 = std::chrono::steady_clock::now();
    for (int i = 0; i < n; ++i) {
        result += f1[i] * f2[i];
    }
    // end time
    auto end1 = std::chrono::steady_clock::now();
    printf("%s%f\n%s%ld%s", "Result is ", result, "calculation takes ", std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1).count(), " ms");
}