#include <iostream>
#include <random>

int main(int, char **) {
    std::random_device rd; // 将用于为随机数引擎获得种子
    std::mt19937 gen(rd());// 以播种标准 mersenne_twister_engine
    std::uniform_int_distribution<> dis(1, 6);
}
