#include <bits/stdc++.h>

// mt19937 随机数生成器
std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());

int main()
{
    const int n = 1e5;
    int a, b;
    a = rnd() % n + 1;
    b = rnd() % n + 1;
    std::cout << a << ' ' << b << std::endl;
    return 0;
}