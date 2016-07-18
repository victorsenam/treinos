#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define lld I64d
#define DEBUG(...) {}
#endif

ll q[2][2];
int t;

ll euclid (ll a, ll & r, ll b, ll & s) {
    ll d, ir, is;
    if (a%b == 0) {
        r = 0;
        s = 1;
        return b;
    }
    d = euclid(b, ir, a%b, is);
    r = is;
    s = ir - is*(a/b);
    return d;
}

bool solve (ll x, ll a, ll b) {
    ll r, s;

    ll d = euclid(a, r, b, s);
    if (x%d)
        return 0;

    //printf("%lld*%lld + %lld*%lld = %lld\n", a, r, b, s, d);
    if (r > s) {
        swap(a, b);
        swap(r, s);
    }

    if (r >= 0) return 1;
    ll m = a*b/d;

    r *= x/d;
    s *= x/d;
    
    ll n = m/a;
    ll k = (-r+n-1)/n;
 //   printf("%lld*%lld\n", k, n);
    r += k*n;
    assert(r >= 0);

    n = m/b;
    s -= k*n;

    //printf("%lld*%lld + %lld*%lld = %lld\n", a, r, b, s, x);

    return s >= 0;

}

int main () {
    scanf("%d", &t);
    while (t--) {
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                scanf("%lld", &q[i][j]);

        bool ok = 0;
        for (int k = 0; !ok && k < 2; k++) {
            ok = 1;
            for (int l = 0; ok && l < 2; l++)
                ok = !(q[1][l]%q[0][k^l]);
        }

        if (ok) {
            printf("YES\n");
            continue;
        }

        if (q[1][0]%q[0][0] || q[1][0]%q[0][1])
            swap(q[1][0], q[1][1]);
        if (q[1][0]%q[0][0] || q[1][0]%q[0][1]) {
            printf("NO\n");
            continue;
        }

        if (solve(q[1][1], q[0][0], q[0][1]))
            printf("YES\n");
        else
            printf("NO\n");
    }
}
