#include "todd_and_steven.h"
#include <message.h>

#include <bits/stdc++.h>
//#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define debug(...) {}
#endif

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const ll MOD = 1e9+7;

inline ll mod (ll x) {
    return (x%MOD);
}

ll c, idx, n[2], jmp;

int main () {
    c = NumberOfNodes();
    idx = MyNodeId();
    if (idx) return 0;

    n[0] = GetToddLength();
    n[1] = GetStevenLength();

    vector<ll> v[2];
    v[0].resize(n[0]);
    v[1].resize(n[1]);

    for (int i = 0; i < n[0]; i++)
        v[0][i] = GetToddValue(i);
    for (int i = 0; i < n[1]; i++)
        v[1][i] = GetStevenValue(i);

    int i = 0;
    int j = 0;
    ll cr = 0;
    ll rs = 0;

    while (i < n[0] || j < n[1]) {
        if (j == n[1] || (i < n[0] && v[0][i] < v[1][j])) {
            rs = mod(rs + (cr^v[0][i]));
            cr++;
            i++;
        } else {
            rs = mod(rs + (cr^v[1][j]));
            cr++;
            j++;
        }
    }

    printf("%lld\n", rs);
}
