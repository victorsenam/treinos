#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

//#define debug(...) {fprintf(stderr, __VA_ARGS__);}
#define debug(...) {}

typedef ll num;

const int N = 5e5+7;
const int M = 1e6+7;

int n, m;
int ts;

vector<ll> pr;
bool sieve[M];

num get (ll x, int k) {
    num ret = 1;
    for (ll p : pr) {
        if (p > x) break;
        int cnt = 0;

        while (x % p == 0) {
            x /= p;
            cnt += k;
        }

        cnt = (cnt%3+3)%3;
        ll loc = 1;
        for (int i = 0; i < cnt; i++)
            loc *= p;
        ret *= loc;

    }
    return ret;
}

int mp[3][M], turn;
ll sv[2][M];

int main () {
    for (int k = 0; k < 2; k++)
        for (int i = 0; i < M; i++)
            sv[k][i] = 1;

    for (ll p = 2; p < M; p++) {
        if (!sieve[p]) {
            int cnt = 1;
            ll a = p;
            ll b = p*p;
            debug("multiplos de: \n");
            for (ll curr = p; curr < M; curr *= p) {
                debug("%lld: ", curr);
                for (ll j = curr; j < M; j += curr) {
                    if ((j/curr)%p == 0) continue;
                    sieve[j] = 1;

                    sv[0][j] *= a;
                    sv[1][j] *= b;
                }
                debug("\n");

                cnt = (cnt+1)%3;
                if (cnt == 0) {
                    a = b = 1;
                } else if (cnt == 1) {
                    a = p;
                    b = p*p;
                } else {
                    a = p*p;
                    b = p;
                }
            }
        }
        printf("%lld : %lld %lld\n", p, sv[0][p], get(p, 1));
        if (sv[0][p] != get(p, 1)) break;
    }

    scanf("%d", &ts);
    while (ts--) {
        turn++;

        ll res = -1;
        scanf("%d %d", &n, &m);

        ll a;
        for (int i = 0; i < n; i++) {
            scanf("%lld", &a);
            ll x = sv[0][a];
            if (mp[2][x] != turn) {
                mp[0][x] = mp[1][x] = 0;
                mp[2][x] = turn;
            }
            mp[0][x]++;
        }
            
        for (int i = 0; i < m; i++) {
            scanf("%lld", &a);
            ll x = sv[1][a];
            if (mp[2][x] != turn) continue;
            mp[1][x]++;

            res = max(res, ll(mp[0][i])*ll(mp[0][i]) + ll(mp[1][i])*ll(mp[1][i]));
        }

        
        printf("%lld\n", res);
    }
}
