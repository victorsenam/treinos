#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef int num;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 1000007;

int n;
ll a, b, t;
char v[N];
ll pos[N], pre[N];

bool solve (int q) {
    if (q == 0)
        return 1;

    ll mini = t+1;

    for (int i = 0; i < q && mini > t; i++) {
        //ll val = pre[i] + pos[n-(q-i-1)] + a*(ll(q-1 + i));
        ll val = pre[i] + pos[n-(q-i-1)] + a*(ll(q-1 + min(i, q-i-1)));
        mini = min(mini, val);
    }

    return (mini <= t);
}

int main () {
    scanf("%d %I64d %I64d %I64d", &n, &a, &b, &t);

    scanf(" %s", v);

    pos[n] = 0;
    for (int i = n-1; i >= 0; i--) {
        pos[i] = pos[i+1] + 1;
        if (v[i] == 'w')
            pos[i] += b;
    }

    pre[0] = 1;
    if (v[0] == 'w')
        pre[0] += b;

    for (int i = 1; i < n; i++) {
        pre[i] = pre[i-1] + 1;
        if (v[i] == 'w')
            pre[i] += b;
    }

    int lo = 0;
    int hi = n;

    while (lo < hi) {
        int mid = (lo+hi+1)/2;

        if (solve(mid))
            lo = mid;
        else
            hi = mid-1;
    }

    printf("%d\n", lo);
}
