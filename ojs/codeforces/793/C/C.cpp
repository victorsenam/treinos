#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define debug(...) {}
#endif

using namespace std;
typedef long long int ll;
typedef long double ld;
typedef pair<int, int> pii;
#define pb push_back

const int N = 1e5+7;
const ld eps = 1e-8;
const ld INF = N;

ll b[4];
ll p[N][2], v[N][2];
int n;

struct quo {
    ll p, q;

    quo (ll a, ll b) {
        if (b == 0) a = 1;

        if (b < 0) {
            a = -a;
            b = -b;
        }
        
        ll g = __gcd(abs(a), b);

        p = a/g;
        q = b/g;
    }

    bool operator < (const quo & ot) const {
        if (q == 0) return 0;
        if (ot.q == 0) return 1;
        return p*ot.q < q*ot.p;
    }
};

void go (quo & lo, quo x) {
    if (x.q == 0) {
        printf("-1\n");
        exit(0);
    }
    if (lo < x)
        lo = x;
}

void tes (quo lo, quo x) {
    if (lo.q == 0) return;
    if (lo < x)
        return;
    printf("-1\n");
    exit(0);
}

quo get (ll p, ll v, ll x) {
    if (p >= x) return quo(0,1);
    if (v <= 0) return quo(1,0);

    return quo(x-p, v);
}

int main () {
    scanf("%d", &n);
    for (int i = 0; i < 4; i++)
        scanf("%lld", &b[i]);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2; j++)
            scanf("%lld", &p[i][j]);
        for (int j = 0; j < 2; j++)
            scanf("%lld", &v[i][j]);
    }

    quo lo(0,1);

    for (int i = 0; i < n; i++) {
        quo a = max(get(p[i][0], v[i][0], b[0]), get(-p[i][0], -v[i][0], -b[2]));
        lo = max(a, lo);
        a = max(get(p[i][1], v[i][1], b[1]), get(-p[i][1], -v[i][1], -b[3]));
        lo = max(a, lo);

    }
    if (lo.q == 0) {
        printf("-1\n");
        return 0;
    }

    for (int i = 0; i < n; i++) {
        quo a = max(get(-p[i][0], -v[i][0], -b[0]), get(p[i][0], v[i][0], b[2]));
        if (!(lo < a)) {
            printf("-1\n");
            return 0;
        }
        a = max(get(-p[i][1], -v[i][1], -b[1]), get(p[i][1], v[i][1], b[3]));
        if (!(lo < a)) {
            printf("-1\n");
            return 0;
        }
    }

    printf("%.20Lf\n", ld(lo.p)/ld(lo.q));
}
