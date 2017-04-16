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

const ll INF = 1e16;

ll h[2];
ll a[2];
int ts;
ll b, d;

ll go (int fase, int turn, ll hp_m, ll hp_d, ll at_m, ll at_d, int rs = 0) {
    if (fase == 3)
        return INF;
    if (hp_d <= 0)
        return 0;
    if (hp_m <= 0)
        return INF;


    ll res = INF;

    if (turn == 1) {
        res = min(res, go(fase, 0, hp_m - at_d, hp_d, at_m, at_d, rs));
    } else {
        res = go(fase+1, 0, hp_m, hp_d, at_m, at_d);
        if (hp_m - at_d <= 0 && rs < 3) {
            res = min(res, go(fase, 1, h[0], hp_d, at_m, at_d, rs+1) + 1);
        }

        if (fase == 0) { // debuff
            if (at_d > 0 && d > 0)
                res = min(res, go(0, 1, hp_m, hp_d, at_m, max(0ll, at_d - d)) + 1);
        } else if (fase == 1) { // buff
            if (at_m < hp_d && b > 0)
                res = min(res, go(1, 1, hp_m, hp_d, at_m + b, at_d) + 1);
        } else if (fase == 2) { // ataque
            res = min(res, go(2, 1, hp_m, hp_d - at_m, at_m, at_d) + 1);
        }
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

        ll res = go(0, 0, h[0], h[1], a[0], a[1]);

        if (res == INF) {
            printf("IMPOSSIBLE\n");
        } else {
            printf("%lld\n", res);
        }
    }
}
