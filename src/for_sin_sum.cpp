//
// Created by lingxd on 2023/2/16.
//
#include <iostream>
#include <vector>
#include <cmath>

#include <oneapi/tbb/tick_count.h>

#define TICK(x) auto bench_##x = tbb::tick_count::now();
#define TOCK(x) std::cout << #x ": " << (tbb::tick_count::now() - bench_##x).seconds() << "s" << std::endl;

int main() {
    size_t n = 1 << 27;
    std::vector<float> a(n);

    TICK(for)
    //fill a with sin(i)
    for (size_t i = 0; i < a.size(); i++) {
        a[i] = std::sin(i);
    }
    TOCK(for)

    TICK(reduce);
    // calculate sum of a
    float res = 0;
    for (float i : a) {
        res += i;
    }
    TOCK(reduce);

    std::cout << res << std::endl;

    return 0;
}