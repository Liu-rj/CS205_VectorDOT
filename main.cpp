#include <iostream>
#include <chrono>
#include <random>
#include <xmmintrin.h>
#include <fstream>
#include <sstream>
//#include <cblas.h>

using namespace std;

float dot1 = 0.0, dot2 = 0.0, dot3 = 0.0, dot4 = 0.0, dot5 = 0.0, dot6 = 0.0;

bool nextL = true;

void block(const float *f1, const float *f2, int i) {
    dot1 += f1[i] * f2[i];
    dot2 += f1[i + 1] * f2[i + 1];
    dot3 += f1[i + 2] * f2[i + 2];
    dot4 += f1[i + 3] * f2[i + 3];
    dot5 += f1[i + 4] * f2[i + 4];
    dot6 += f1[i + 5] * f2[i + 5];
}

//float block(const float *f1, const float *f2, int i) {
//    return f1[i] * f2[i] + f1[i + 1] * f2[i + 1] + f1[i + 2] * f2[i + 2]
//           + f1[i + 3] * f2[i + 3] + f1[i + 4] * f2[i + 4] + f1[i + 5] * f2[i + 5];
//}

//float sse_inner(const float *a, const float *b, unsigned int size) {
//    float z = 0.0f, fres = 0.0f;
//    float ftmp[4] = {0.0f, 0.0f, 0.0f, 0.0f};
//    __m128 mres;
//
//    if ((size / 4) != 0) {
//        mres = _mm_load_ss(&z);
//        for (unsigned int i = 0; i < size / 4; i++) {
//            mres = _mm_add_ps(mres, _mm_mul_ps(_mm_loadu_ps(&a[4 * i]), _mm_loadu_ps(&b[4 * i])));
//        }
//
//        __m128 mv1 = _mm_movelh_ps(mres, mres);
//        __m128 mv2 = _mm_movehl_ps(mres, mres);
//        mres = _mm_add_ps(mv1, mv2);
//
//        _mm_store_ps(ftmp, mres);
//
//        fres = ftmp[0] + ftmp[1];
//    }
//
//    if ((size % 4) != 0) {
//        for (unsigned int i = size - size % 4; i < size; i++) {
//            fres += a[i] * b[i];
//        }
//    }
//
//    return fres;
//}

float isNum(const string &s) {
    stringstream sin(s);
    float t;
    char p;
    if (s.find('#') != string::npos) {
        cout << "see you!";
        exit(0);
    } else {
        if (!(sin >> t)) {
            cout << "wrong input, please input again!" << endl;
            nextL = false;
        }
        if (sin >> p) {
            cout << "wrong input, please input again!" << endl;
            nextL = false;
        }
    }
    return t;
}

int judgeN(const string &s) {
    stringstream sin(s);
    char p;
    int n = 0;
    if (s.find('#') != string::npos) {
        cout << "see you!";
        exit(0);
    } else {
        if (!(sin >> n)) {
            cout << "wrong input, please input again!" << endl;
            nextL = false;
        }
        if (sin >> p) {
            cout << "wrong input, please input again!" << endl;
            nextL = false;
        }
    }
    if (n <= 0) {
        cout << "wrong input, please input again!" << endl;
        nextL = false;
    }
    return n;
}

int main() {
    int n;
    string s;

    cout << "(exit with #)" << endl;

    while (nextL) {
        cout << "Please input your vector's length:" << endl;
        cin >> s;

        // 判断输入是否合法
        n = judgeN(s);
        if (!nextL) {
            nextL = true;
            continue;
        }

        auto *f1 = new float[n];
        auto *f2 = new float[n];
        float result = 0.0;

        cout << "Please input the first vector:" << endl;
        for (int i = 0; i < n; ++i) {
            cin >> s;
            f1[i] = isNum(s);
        }
        if (!nextL) {
            nextL = true;
            continue;
        }

        cout << "Please input the second vector:" << endl;
        for (int i = 0; i < n; ++i) {
            cin >> s;
            f2[i] = isNum(s);
        }
        if (!nextL) {
            nextL = true;
            continue;
        }

        // begin time
        auto start1 = std::chrono::steady_clock::now();

        /**
         * OpenBLAS
         */
//    result += cblas_sdot(n, f1, 1, f2, 1);

        /**
         * SSE
         */
//    result += sse_inner(f1, f2, n);

        /**
         * Block
         */
//    int m = n % 6;
//    for (int i = 0; i < m; ++i) {
//        result += f1[i] * f2[i];
//    }
//    for (int i = m; i < n; i += 6) {
//        result += block(f1, f2, i);
//    }

        /**
         * parallel
         */
        int m = n % 6;
        for (int i = 0; i < m; ++i) {
            result += f1[i] * f2[i];
        }
        for (int i = m; i < n; i += 6) {
            block(f1, f2, i);
        }
        result += dot1 + dot2 + dot3 + dot4 + dot5 + dot6;

        /**
         * brutal
         */
//    for (int i = 0; i < n; ++i) {
//        result += f1[i] * f2[i];
//    }
        // end time
        auto end1 = std::chrono::steady_clock::now();
        printf("%s%f\n%s%ld%s", "Result is ", result, "calculation takes ",
               std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1).count(), " ms\n");
        dot1 = 0, dot2 = 0, dot3 = 0, dot4 = 0, dot5 = 0, dot6 = 0;
        delete[] f1;
        delete[] f2;
    }
}

/**
 * brutal(float):-365884255676600942592.000000 1165 ms
 * brutal(double):-364535047238995935232.000000 1206 ms
 * brutal(vector):-365884255676600942592.000000 2042 ms
 * block:-364864823679699124224.000000 427 ms
 * parallel:-364598196508009955328.000000 328 ms
 * SSE:-363692691507931774976.000000 217 ms
 * OpenBLAS:-364535040560110501888.000000 116ms
 */