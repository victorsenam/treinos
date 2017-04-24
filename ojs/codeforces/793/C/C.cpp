#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define debug(...) {}
#endif

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 1e5+7;

int n;
ll w[2][2];
ll p[N][2][2];

struct quo {
    ll p, q;

    quo (ll a, ll b) {
        if (a == 0)
            b = 1;

        if (b < 0) {
            b = -b;
            a = -a;
        }

        ll g = __gcd(abs(a),b);
        p = a/g;
        q = b/g;
    }

    bool operator < (const quo & x) const {
        if (!q && !x.q)
            return p < x.p;
        return p*x.q < q*x.p;
    }
};

int main () {
    scanf("%d", &n);

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            scanf("%lld", &w[i][j]);


    quo lo(0,1);
    quo hi(1,0);

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                scanf("%lld", &p[k][i][j]);
        
        for (int j = 0; j < 2; j++) {
            quo a(w[0][j] - p[k][0][j], p[k][1][j]);
            quo b(w[1][j] - p[k][0][j], p[k][1][j]);

            if (p[k][1][j] == 0) {
                if (p[k][0][j] <= w[0][j] || p[k][0][j] >= w[1][j])
                    lo = quo(1,0);
            }

            if (b < a)
                swap(a, b);

            lo = max(a, lo);
            hi = min(b, hi);
        }
    }

    if (lo < hi)
        printf("%.20f\n", double(lo.p)/double(lo.q));
    else
        printf("-1\n");
}

