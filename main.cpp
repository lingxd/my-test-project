#include <algorithm>
#include <iostream>
#include <iterator>
#include <random>
#include <vector>

class D {

};

class C : public D {
protected:
    virtual void a() const {
        std::cout << "class D a()" << std::endl;
    };
};

class B : public C
{
protected:
    void a() const override {
        std::cout << "class B a()" << std::endl;
    };
};

class A : public B {

protected:
    void a() const override {
        std::cout << "class A a()" << std::endl;
    };
public:
    A() {
        C::a();
        B::a();
        A::a();
    };
};


int main(int, char **) {
    std::random_device rd; // 将用于为随机数引擎获得种子
    std::mt19937 gen(rd());// 以播种标准 mersenne_twister_engine
    std::uniform_int_distribution<> dis(1, 100);

    //    std::vector<int> rand_v = {dis(gen), dis(gen), dis(gen), dis(gen), dis(gen), dis(gen), dis(gen)};
    std::vector<int> v{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1};
    for (const auto &it: v) {
        std::cout << it << "\t";
    }
    std::cout << std::endl;

    auto ret2 = std::count(v.begin(), v.end(), 1);
    (ret2)
        ? std::cout << "找到【1】的个数： " << ret2 << "\n"
        : std::cout << "没找到" << "\n";

    std::sort(v.begin(), v.end(), std::greater<>());
    std::cout << "最大两个数字：" << v.at(0) << " " << v.at(1);
    std::cout << std::endl;
    A a;
}
