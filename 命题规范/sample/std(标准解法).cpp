#include <bits/stdc++.h>
using namespace std;
const int N = 2e6 + 5;
int main()
{
    int n;
    cin >> n;
    vector<int> arr(n);
    for (auto& i : arr)
        cin >> i;

    bitset<N> a, b;
    a[arr[0] + 1e6] = 1;
    for (int i = 1; i < n; ++i)
    {
        b |= a >> abs(arr[i]);
        b |= a << abs(arr[i]);
        a = b;
        b = 0;
    }
    int q;
    cin >> q;
    while (q--)
    {
        int m;
        cin >> m;
        if (a[m + 1e6])
            cout << "Yes\n";
        else
            cout << "No\n";
    }
    return 0;
}