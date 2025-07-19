#include <bits/stdc++.h>
#include <ranges>
using namespace std;
using ll = long long;

struct P
{
    ll x, y;
    P(ll x = 0, ll y = 0) : x(x), y(y) {}
};

// 有理数的分数表达 常用于斜率/截距等可能会爆精度的地方
// 需要点线问题 需要 P
struct Rational
{
    using ll = long long;
    ll num, den; // 表示 num/den

    Rational()
    {
        num = 1;
        den = 1;
    }
    Rational(ll _num = 0, ll _den = 1)
    {
        if (_den < 0)
        {
            _num = -_num;
            _den = -_den;
        }
        num = _num;
        den = _den;
        normalize();
    }
    void normalize()
    {
        if (den == 0)
            return; // 特殊情况
        ll g = __gcd(num, den);
        if (g != 0)
        {
            num /= g;
            den /= g;
        }
        if (num < 0)
        {
            num = -num;
            den = -den;
        }
    }

    Rational rev() const
    {
        return Rational(den, num);
    }

    Rational operator+(const Rational &other) const
    {
        Rational re = Rational(num * other.den + other.num * den, den * other.den);
        return re;
    }
    Rational operator-(const Rational &other) const
    {
        Rational re = Rational(num * other.den - other.num * den, den * other.den);
        return re;
    }
    Rational operator*(const Rational &other) const
    {
        Rational re = Rational(num * other.num, den * other.den);
        return re;
    }
    Rational operator/(const Rational &other) const
    {
        Rational re = *this * other.rev();
        return re;
    }

    bool operator==(const Rational &other) const
    {
        return num == other.num && den == other.den;
    }
    bool operator<(const Rational &other) const
    {
        // a/b < c/d <=> a*d < c*b
        // return num * other.den < other.num * den;
        if (!den && !other.den)
        {
            return num < other.num;
        }
        else if (!den)
        {
            return false;
        }
        else if (!other.den)
        {
            return true;
        }
        else
        {
            return (*this - other).num < 0;
        }
    }
};

// 为 unordered_map 定义 hash
struct RationalHash
{
    size_t operator()(const Rational &r) const
    {
        auto h1 = std::hash<ll>()(r.num);
        auto h2 = std::hash<ll>()(r.den);
        return h1 ^ (h2 + 0x9e3779b97f4a7c15ULL + (h1 << 6) + (h1 >> 2));
    }
};

// 计算两点之间的斜率，返回有理数表示形式
// 对于竖直线，统一返回 Rational(1, 0)
Rational getSlope(const P &a, const P &b)
{
    ll dx = b.x - a.x, dy = b.y - a.y;
    if (dx == 0)
        return Rational(1, 0); // 表示竖直线
    return Rational(dy, dx);
}

// 根据候选斜率和点，计算截距的有理数表示（非竖直线：b = (y*dx - x*dy)/dx；竖直线直接返回 x 值，分母设为1）
Rational getIntercept(const P &p, const Rational &slope)
{
    if (slope.den == 0)
    { // 竖直线
        return Rational(p.x, 1);
    }
    // b = y - (dy/dx)*x = (y*dx - dy*x)/dx
    ll num = p.y * slope.den - p.x * slope.num;
    ll den = slope.den;
    return Rational(num, den);
}