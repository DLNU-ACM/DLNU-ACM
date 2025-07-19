#include <bits/stdc++.h>

using namespace std;

template <class T>
class MaxFlow
{
    using ll = long long;

private:
    struct edge
    {
        ll to;
        T cap;
        edge(ll v, T c) : to(v), cap(c) {};
    };

    ll n;                 // 点的数量
    vector<edge> e;       // 边集
    vector<vector<ll>> g; // 邻接表
    vector<ll> cur, h;    // cur: 当前弧优化 h: 深度

    void init(ll n)
    {
        this->n = n;
        e.clear();
        g.assign(n, {});
        cur.resize(n);
        h.resize(n);
    }

    // 对点分层 寻找增广路
    bool bfs(ll s, ll t)
    {
        h.assign(n, -1);
        queue<ll> q;
        h[s] = 0;
        q.emplace(s);
        while (!q.empty())
        {
            ll u = q.front();
            q.pop();
            for (auto &i : g[u])
            {
                auto &[v, c] = e[i];
                if (c > 0 && h[v] == -1)
                {
                    h[v] = h[u] + 1;
                    if (v == t)
                        return true;
                    q.emplace(v);
                }
            }
        }
        return false;
    }

    T dfs(ll u, ll t, T f)
    {
        if (u == t)
        {
            return f;
        }
        auto r = f;

        for (ll &i = cur[u]; i < ll(g[u].size()); ++i)
        {
            ll j = g[u][i];
            auto [v, c] = e[j];

            // 分层优化
            if (c > 0 && h[v] == h[u] + 1)
            {
                auto a = dfs(v, t, min(r, c));

                // 更新残留网
                e[j].cap -= a;
                e[j ^ 1].cap += a;

                r -= a;

                // 剩余流量优化
                if (r == 0)
                    return f;
            }
        }
        if (r == f)
            h[u] = 0;
        return f - r;
    }

public:
    MaxFlow() {}
    MaxFlow(ll n)
    {
        init(n);
    }

    void addEdge(ll u, ll v, T c)
    {
        g[u].emplace_back(e.size());
        e.emplace_back(v, c);
        g[v].emplace_back(e.size());
        e.emplace_back(u, 0);
    }

    T flow(ll s, ll t)
    {
        T re{};
        while (bfs(s, t))
        {
            cur.assign(n, 0);
            re += dfs(s, t, numeric_limits<T>::max());
        }
        return re;
    }
};
