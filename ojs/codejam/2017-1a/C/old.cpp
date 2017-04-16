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

ll h[2];
ll a[2];
int ts;
ll b, d;

ll go (ll atk, ll cur, ll shi) {
    ll hp = h[1];
    ll rs = 0;

    int rp = 0;
    while (hp > 0ll) {
        if (cur - a[1] <= 0) {
            rs++;
            cur = h[0] - a[1];
            if (rp == 3)
                return LLONG_MAX;
            rp++;
        } else {
            rp = 0;
            hp -= atk;
            cur -= a[1];
        }
    }

    return rs + shi;
}

ll solve (ll cur, ll sh) {
    ll atk = a[0];
    ll res = LLONG_MAX;

    int rp = 0;
    while (rp < 3) {
        res = min(res, go(atk, cur, sh));
        
        if (b == 0 || atk >= h[1])
            break;

        if (a[1] >= cur) {
            cur = h[0] - a[1];
            rp++;
        } else {
            rp = 0;
            atk += b;
            cur -= a[1];
        }

        sh++;
    }

    return res;
}

int main () {
    scanf("%d", &ts);

    for (int tt = 1; tt <= ts; tt++) {
        printf("Case #%d: ", tt);
        for (int i = 0; i < 2; i++)
            scanf("%lld %lld", &h[i], &a[i]);
        scanf("%lld %lld", &b, &d);

        ll res = LLONG_MAX;
        ll att = 0;
        ll cur = h[0];
        int rp = 0;
        while (rp < 3) {
            res = min(res, solve(cur, att));

            if (d == 0 || a[1] == 0)
                break;

            if (max(a[1] - d, 0ll) >= cur) {
                cur = h[0] - a[1];
                rp++;
            } else {
                rp = 0;
                a[1] -= d;
                a[1] = max(a[1], 0ll);
                cur -= a[1];
            }

            att++;
        }

        if (rp == 3 || res == LLONG_MAX) {
            printf("IMPOSSIBLE\n");
        } else {
            printf("%lld\n", res);
        }
    }
}
