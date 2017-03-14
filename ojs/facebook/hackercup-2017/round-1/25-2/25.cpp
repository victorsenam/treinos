#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;

const int N = 1e2+7;
const int M = 1e4+7;
const ll INF = ll(M)*ll(N)*ll(1000);

int ts;
int n, m, k;
int s[M][2];

ll dist[N][N];
ll memo[M];
int visi[M], turn;

void floyd () {
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
}

ll pd (int i) {
    if (i == k+1) 
        return 0;
    ll & me = memo[i];
    if (visi[i] == turn)
        return me;
    visi[i] = turn;
    me = INF;

    me = min(me, dist[s[i][0]][s[i][1]] + dist[s[i][1]][s[i+1][0]] + pd(i+1));
    if (i < k)
        me = min(me, dist[s[i][0]][s[i+1][0]] + dist[s[i+1][0]][s[i][1]] + dist[s[i][1]][s[i+1][1]] + dist[s[i+1][1]][s[i+2][0]] + pd(i+2));
    return me;
}

int main () {
    scanf("%d", &ts);

    while (ts--) {
        turn++;
        scanf("%d %d %d", &n, &m, &k);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                dist[i][j] = INF;
            dist[i][i] = 0;
        }

        for (int i = 0; i < m; i++) {
            int a, b;
            ll w;
            scanf("%d %d %lld", &a, &b, &w);
            a--; b--;
            dist[a][b] = min(dist[a][b], w);
            dist[b][a] = min(dist[b][a], w);
        }

        floyd();

        for (int i = 1; i <= k; i++) {
            scanf("%d %d", &s[i][0], &s[i][1]);           
            s[i][0]--; s[i][1]--;
        }
        s[k+1][0] = s[k][1];

        ll res = pd(0);
        if (res == INF)
            res = -1;
        printf("Case #%d: %lld\n", turn, res);
    }
}
