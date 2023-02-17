//
// Created by lingxd on 2023/2/16.
//

#include <iostream>
#include <oneapi/tbb/parallel_reduce.h>
#include <oneapi/tbb/blocked_range.h>
#include <oneapi/tbb/parallel_for.h>
#include <vector>
#include <cmath>

//#include <chrono>
//#define TICK(x) auto bench_##x = std::chrono::steady_clock::now();
//#define TOCK(x) std::cout << #x ": " << std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::steady_clock::now() - bench_##x).count() << "s" << std::endl;

#include <oneapi/tbb/tick_count.h>
#define TICK(x) auto bench_##x = tbb::tick_count::now();
#define TOCK(x) std::cout << #x ": " << (tbb::tick_count::now() - bench_##x).seconds() << "s" << std::endl;

int main() {
    size_t n = 1 << 27;
    std::vector<float> a(n);

    TICK(for)
    //fill a with sin(i)
    tbb::parallel_for(tbb::blocked_range<size_t>(0, n),
            [&] (tbb::blocked_range<size_t> r) {
        for (size_t i = r.begin(); i < r.end(); i++) {
            a[i] = std::sin(i);
        }
    });
    TOCK(for)

    TICK(reduce);
    // calculate sum of a
    auto res = tbb::parallel_reduce(tbb::blocked_range<size_t>(0, n), (float)0, [&] (tbb::blocked_range<size_t> r, float local_res) {
        for (size_t i = r.begin(); i < r.end(); i++) {
            local_res += a[i];
        }
        return local_res;
    }, [] (float x, float y) {
        return x + y;
    });
    TOCK(reduce);

    std::cout << res << std::endl;

    return 0;
}