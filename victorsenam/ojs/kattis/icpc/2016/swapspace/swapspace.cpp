#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;

const int N = 1e6+7;

struct node {
    ll ini;
    ll win;

    bool operator < (const node & ot) const
    { return win < ot.win; }
};

node v[N], u[N];
int n, m;
multiset<node> s;
ll sumall;

bool cmp_t (const node & a, const node & b) {
    return a.ini < b.ini;
}

bool cmp_s (const node & a, const node & b) {
    return a.ini + a.win < b.ini + b.win;
}

bool solve (ll t) {
    ll l = 0;
    ll c = 0;

    for (l = 0; l < n && v[l].ini <= t + c; l++)
        c += v[l].win;
    if (l < n) 
        return 0;

    c = sumall;

    for (l = 0; l < m && u[l].ini <= t + c - u[l].win; l++) {
        c -= u[l].win;
    }
    if (l < m)
        return 0;

    return 1;
}

int main () {
    scanf("%d", &n);

    m = 0;
    for (int i = 0; i < n; i++) {
        scanf("%lld %lld", &v[i].ini, &v[i].win);
        v[i].win -= v[i].ini;
        sumall += v[i].win;

        if (v[i].win < 0) {
            u[m] = v[i];
            m++; i--; n--;
        }
    }

    sort(v, v+n, cmp_t);
    sort(u, u+m, cmp_s);

    ll lo = 0;
    ll hi = 1e17+3;

    while (lo < hi) {
        ll mid = lo + (hi - lo)/2;

        if (solve(mid))
            hi = mid;
        else
            lo = mid+1;
    }

    printf("%lld\n", lo);
}
