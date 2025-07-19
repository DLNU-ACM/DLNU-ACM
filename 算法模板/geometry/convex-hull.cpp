#include <bits/stdc++.h>
#include <ranges>
using namespace std;

using ll = long long;

struct P
{
    ll x, y;
    P(ll x = 0, ll y = 0) : x(x), y(y) {}
};

bool operator==(const P &a, const P &b)
{
    return a.x == b.x && a.y == b.y;
}

P operator+(const P &a, const P &b)
{
    return P(a.x + b.x, a.y + b.y);
}
P operator-(const P &a, const P &b)
{
    return P(a.x - b.x, a.y - b.y);
}

ll dot(const P &a, const P &b)
{
    return a.x * b.x + a.y * b.y;
}

ll cross(const P &a, const P &b)
{
    return a.x * b.y - a.y * b.x;
}

void norm(vector<P> &h)
{
    ll i{};
    for (ll j{}; j < h.size(); ++j)
    {
        if (h[j].y < h[i].y || (h[j].y == h[i].y && h[j].x < h[i].x))
        {
            i = j;
        }
    }
    rotate(h.begin(), h.begin() + i, h.end());
}

ll sgn(P &a)
{
    return a.y > 0 || (a.y == 0 && a.x > 0) ? 0 : 1;
}

vector<P> gethull(vector<P> p)
{
    vector<P> h, l;
    sort(p.begin(), p.end(), [&](auto a, auto b) -> bool
         {
        if(a.x != b.x)
        {
            return a.x < b.x;
        }else{
            return a.y < b.y;
        } });
    p.erase(unique(p.begin(), p.end()), p.end());

    if (p.size() <= 1)
    {
        return p;
    }

    for (auto a : p)
    {
        while (h.size() > 1 && cross(a - h.back(), a - h[h.size() - 2]) <= 0)
        {
            h.pop_back();
        }
        while (l.size() > 1 && cross(a - l.back(), a - l[l.size() - 2]) >= 0)
        {
            l.pop_back();
        }
        l.emplace_back(a);
        h.emplace_back(a);
    }

    l.pop_back();
    reverse(h.begin(), h.end());
    h.pop_back();
    l.insert(l.end(), h.begin(), h.end());
    return l;
}