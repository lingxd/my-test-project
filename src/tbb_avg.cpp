//
// Created by lingxd on 2023/2/14.
//

#include <iostream>
#include <oneapi/tbb/parallel_reduce.h>
#include <oneapi/tbb/blocked_range.h>
#include <vector>
#include <cmath>

//#include <chrono>
//#define TICK(x) auto bench_##x = std::chrono::steady_clock::now();
//#define TOCK(x) std::cout << #x ": " << std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::steady_clock::now() - bench_##x).count() << "s" << std::endl;

#include <oneapi/tbb/tick_count.h>
#define TICK(x) auto bench_##x = tbb::tick_count::now();
#define TOCK(x) std::cout << #x ": " << (tbb::tick_count::now() - bench_##x).seconds() << "s" << std::endl;

int main() {
    size_t n = 1 << 26;
    std::vector<float> a(n);
    for (size_t i = 0; i < a.size(); i++) {
        a[i] = std::sin(i);
    }

    TICK(for)

    float serial_avg = 0;
    for (float i : a) {
        serial_avg += i;
    }
    serial_avg /= n;
    std::cout << serial_avg << std::endl;

    TOCK(for)

    TICK(reduce)
    auto parallel_avg = tbb::parallel_reduce(tbb::blocked_range<size_t>(0, n), (float)0,
                                    [&] (tbb::blocked_range<size_t> r, float local_avg) {
                                        for (size_t i = r.begin(); i < r.end(); i++) {
                                            local_avg += a[i];
                                        }
                                        return local_avg;
                                    }, [] (float x, float y) {
                return x + y;
            }) / n;

    std::cout << parallel_avg << std::endl;
    TOCK(reduce)

    return 0;
}