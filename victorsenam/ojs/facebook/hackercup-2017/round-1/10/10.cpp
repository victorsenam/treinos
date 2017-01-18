#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;

const int N = 307;
const ll INF = ll(N)*ll(1e6+N);

ll memo[N][N];
int visi[N][N], turn;
int t, n, m;
ll c[N][N];

ll pd (int i, int x) {
    if (x < 0) return INF;
    if (i == n) return 0;
    ll & me = memo[i][x];
    if (visi[i][x] == turn)
        return me;
    visi[i][x] = turn;
    
    me = INF;
    ll acc = 0;
    for (ll j = 0; j <= m; j++) {
        me = min(me, acc + j * j + pd(i+1, x+j-1));
        acc += c[i][j];
    }

    return me;
}

int main () {
    scanf("%d", &t);

    while (t--) {
        turn++;
        scanf("%d %d", &n, &m);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++)
                scanf("%lld", &c[i][j]);
            sort(c[i], c[i]+m);
        }

        printf("Case #%d: %lld\n", turn, pd(0, 0));
    }
}
