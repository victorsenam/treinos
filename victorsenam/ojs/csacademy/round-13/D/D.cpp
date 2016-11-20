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

ll sieve[M];
ll mp[3][M], turn;
ll sv[2][M];

int main () {
    sv[0][1] = sv[1][1] = 1;
    for (ll p = 2; p < M; p++) {
        if (!sieve[p]) {
            for (ll j = p; j < M; j += p) {
                sieve[j] = p;
            }
        }

        ll x = p;
        int cnt = 0;
        while (x % sieve[p] == 0) {
            cnt++;
            x /= sieve[p];
        }

        cnt %= 3;

        ll a = sieve[p];
        ll b = sieve[p]*sieve[p];
        if (cnt == 2) swap(a, b);
        else if (cnt == 0) a = b = 1;

        sv[0][p] = sv[0][x]*a;
        sv[1][p] = sv[1][x]*b;
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
            if (x >= M) continue;
            if (mp[2][x] != turn) continue;
            mp[1][x]++;

            res = max(res, ll(mp[0][x])*ll(mp[0][x]) + ll(mp[1][x])*ll(mp[1][x]));
        }

        
        printf("%lld\n", res);
    }
}
