#include <bits/stdc++.h>
using namespace std;
// 随机数生成器，也可以使用testlib或其他库
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
int main()
{
    // 生成一个随机长度的数组，长度在1到1000之间
    int n = rnd() % 1000 + 1;
    vector<int> arr(n);
    // 数组元素在-1000到1000之间
    for (int i = 0; i < n; ++i)
        arr[i] = (long long)(rnd() % 2001) - 1000;

    bitset<(int)2e6 + 5> a, b;
    a[arr[0] + 1e6] = 1;
    for (int i = 1; i < n; ++i)
    {
        b |= (a >> abs(arr[i]));
        b |= (a << abs(arr[i]));
        a = b;
        b &= 0;
    }
    vector<int> res;
    // 计算结果，存储在res中
    for (int i = 0; i < 2e6 + 5; ++i)
    {
        if (a[i] == 1)
            res.push_back(i - 1e6);
    }
    int S = res.size();

    // q是查询次数，范围在1到1e5之间
    int q = rnd() % 100000 + 1;
    cout << n << '\n';
    for (auto i : arr)
        cout << i << ' ';
    cout << '\n';
    cout << q << '\n';
    //
    while (q--)
    {
        // 随机选择查询方式
        // 有两种查询方式：1.查询一个随机的结果（确保存在）2.查询一个随机的整数(不一定存在)
        // 查询一个随机的结果时，从res中随机选择一个元素输出
        // 查询一个随机的整数时，输出一个范围在-1000000到1000000之间的整数
        int rorw = rnd() % 2;
        if (rorw)
        {
            int idx = rnd() % S;
            cout << res[idx] << '\n';
        }
        else
        {
            // 查询一个随机的整数, t的范围在-1e6到1e6之间
            int t = (long long)(rnd() % 2000001) - 1000000;
            cout << t << '\n';
        }
    }
    return 0;
}