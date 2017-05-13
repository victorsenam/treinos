#include <message.h>
#include "almost_sorted.h"

#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define debug(...) {}
#endif

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

int n, k, c, id;
int jmp, l, r;

inline ll mod (ll x) {
    return (x&((1ll<<20)-1));
}

int main () {
    n = NumberOfFiles();
    k = MaxDistance();
    c = NumberOfNodes() - 1;
    id = MyNodeId();

    c = min(c, n);
    if (id > c) return 0;

    jmp = (n+c-1)/c;
    l = id*jmp;
    r = min(n, l+jmp);

    if (id == c) {
        ll res = 0;
        for (int i = 0; i < c; i++) {
            Receive(i);
            res = mod(res + GetInt(i));
        }
        printf("%lld\n", res);
    } else {
        int ql = max(l-k, 0);
        int qr = min(r+k, n);
        vector<ll> v(qr-ql);

        for (int i = 0; i < v.size(); i++)
            v[i] = Identifier(i+ql);
        sort(v.begin(), v.end());

        ll res = 0;
        for (ll i = l; i < r; i++)
            res = mod(res + mod(v[i-ql]*i));
        PutInt(c, int(res));
        Send(c);
    }
}
