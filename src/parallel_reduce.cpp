//
// Created by lingxd on 2023/2/14.
//

#include <iostream>
#include <oneapi/tbb/parallel_reduce.h>
#include <oneapi/tbb/blocked_range.h>
#include <vector>
#include <cmath>

int main() {
    size_t n = 1 << 26;
    auto res = tbb::parallel_reduce(tbb::blocked_range<size_t>(0, n), (float)0,
            [&] (tbb::blocked_range<size_t> r, float local_res) {
                for (size_t i = r.begin(); i < r.end(); i++) {
                    a[i] = std::sin(i);
                }
                return local_res;
    }, [] (float x, float y) {
        return x + y;
    });

    std::cout << res << std::endl;

    return 0;
}
