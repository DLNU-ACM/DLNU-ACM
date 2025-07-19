#include <bits/stdc++.h>

using namespace std;

template <typename T>
class Fenwick
{
    using ll = long long;

private:
    ll n;
    vector<T> v;

    void init(ll n_)
    {
        n = n_;
        v.assign(n, T{});
    }

public:
    // 使用下标 1 <= i <= n
    Fenwick(ll n_ = 0)
    {
        init(n_ + 1);
    };

    void add(ll x, T &val)
    {
        for (ll i = x; i < n; i += (i & -i))
        {
            v[i] = v[i] + val;
        }
    }

    T sum(ll x)
    {
        T re{};
        for (ll i = x; i > 0; i -= (i & -i))
        {
            re = re + v[i];
        }
        return re;
    }

    T rangeSum(ll l, ll r)
    {
        return sum(r) - sum(l - 1);
    }
};
