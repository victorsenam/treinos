#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#endif

using namespace std;
typedef long long int ll;

ll m, h[2], c[2], x[2], y[2];
ll a, b;
ll cy[2], sh[2];

void solve (int k) {
    ll s = h[k];
    cy[k] = 0;
    sh[k] = -1;
    
    do {
        if (h[k] == c[k])
            sh[k] = cy[k];
        cy[k]++;

        h[k] = (h[k]*x[k] + y[k])%m;
    } while (s != h[k]);
}

int main () {
    scanf("%lld", &m);

    for (int k = 0; k < 2; k++) {
        scanf("%lld %lld", &h[k], &c[k]);
        scanf("%lld %lld", &x[k], &y[k]);
        solve(k);

        if (sh[k] == -1) {
            printf("-1\n");
            return 0;
        }
    }
    debug("%lld %lld\n", cy[0], cy[1]); 

    ll r[2] = {1, 0}, s[2] = {0, 1};
    cy[1] = -cy[1];

    ll a = cy[0], b = cy[1];

    while (a % b) {
        ll q = a/b;

        swap(a, b);
        b %= a;

        r[0] -= (r[1] * q);
        swap(r[0], r[1]);
        s[0] -= (s[1] * q);
        swap(s[0], s[1]);
    }

    debug("(%lld) * (%lld) + (%lld) * (%lld) = %lld\n", r[1], cy[0], s[1], cy[1], b);

    ll c = sh[1] - sh[0];

    if (c % b) {
        printf("-1\n");
        return 0;
    }

    ll q = cy[1]/b;
    ll fx = r[1]/q;

    q = cy[0]/b;
    fx = min(fx, s[1]/q);

    fx *= cy[1]/b;

    debug("(%lld) * (%lld) + (%lld) = ", r[1]-fx, cy[0], sh[0]);
    printf("%lld\n", (r[1]-fx)*cy[0] + sh[0]);
}
