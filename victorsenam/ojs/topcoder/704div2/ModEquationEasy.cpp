#line 2 "ModEquationEasy.cpp"
#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

const int N = 102;
const ll MOD = 1e9+7;

map<int, ll> memo[N];
int m, o, k;

ll pd (int i, int v) {
    if (memo[v].find(i) != memo[v].end())
        return memo[v][i];
    ll me = 0;
    
    if (i == 0)
        return memo[v][i] = (v == 1);
    if (i == 1)
        return memo[v][i] = 1;

    for (int x = 0; x < k; x++)
        for (int y = 0; y < k; y++) {
            if ((x*y)%k != v)
                continue;
            me = (me + ((pd(i/2, x)*pd((i+1)/2, y))%MOD))%MOD;
        }

    return memo[v][i] = me;
}

class ModEquationEasy {
    public:
    int count(int n, int K, int v) {
        k = K;
        return pd(n, v);
    }
};
