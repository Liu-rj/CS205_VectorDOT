#include <iostream>
#include <chrono>
#include <random>
#include <xmmintrin.h>

using namespace std;

float dot1 = 0.0, dot2 = 0.0, dot3 = 0.0, dot4 = 0.0, dot5 = 0.0, dot6 = 0.0;

void block(const float *f1, const float *f2, int i) {
    dot1 += f1[i] * f2[i];
    dot2 += f1[i + 1] * f2[i + 1];
    dot3 += f1[i + 2] * f2[i + 2];
    dot4 += f1[i + 3] * f2[i + 3];
    dot5 += f1[i + 4] * f2[i + 4];
    dot6 += f1[i + 5] * f2[i + 5];
}

float sse_inner(const float *a, const float *b, unsigned int size) {
    float z = 0.0f, fres = 0.0f;
    float ftmp[4] = {0.0f, 0.0f, 0.0f, 0.0f};
    __m128 mres;

    if ((size / 4) != 0) {
        mres = _mm_load_ss(&z);
        for (unsigned int i = 0; i < size / 4; i++) {
            mres = _mm_add_ps(mres, _mm_mul_ps(_mm_loadu_ps(&a[4 * i]), _mm_loadu_ps(&b[4 * i])));
        }

        __m128 mv1 = _mm_movelh_ps(mres, mres);
        __m128 mv2 = _mm_movehl_ps(mres, mres);     //c,d,c,d
        mres = _mm_add_ps(mv1, mv2);                //res[0],res[1]

        _mm_store_ps(ftmp, mres);

        fres = ftmp[0] + ftmp[1];
    }

    if ((size % 4) != 0) {
        for (unsigned int i = size - size % 4; i < size; i++) {
            fres += a[i] * b[i];
        }
    }

    return fres;
}

int main() {
    int n = 200000000;
    random_device r;
    default_random_engine e(r());
    uniform_real_distribution<float> uniform_dist(-1000000000, 1000000000);
    auto *f1 = new float[n];
    auto *f2 = new float[n];
    float result = 0.0;

    cout << "(exit with #)" << endl << "Please input your vector's length:" << endl << "Please input the first vector:"
         << endl;
    for (int i = 0; i < n; ++i) {
        f1[i] = uniform_dist(e);
    }

    cout << "Please input the second vector:" << endl;
    for (int i = 0; i < n; ++i) {
        f2[i] = uniform_dist(e);
    }

    // begin time
    auto start1 = std::chrono::steady_clock::now();
//    result += sse_inner(f1, f2, n);
    int m = n % 6;
    for (int i = 0; i < m; ++i) {
        result += f1[i] * f2[i];
    }
    for (int i = m; i < n; i += 6) {
        block(f1, f2, i);
    }
    result += dot1 + dot2 + dot3 + dot4 + dot5 + dot6;
    // end time
    auto end1 = std::chrono::steady_clock::now();
    printf("%s%f\n%s%ld%s", "Result is ", result, "calculation takes ",
           std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1).count(), " ms");
}