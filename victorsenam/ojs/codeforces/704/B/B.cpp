#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 5007;
const int K = 8;
const ll inf = ll(5e12)+3ll;

ll memo[2][N];
int n, s, e;
ll v[N][5];

int main () {
    scanf("%d %d %d", &n, &s, &e);

    s--; e--;

    for (int i = 0; i < 5; i++)
        for (int j = 0; j < n; j++)
            scanf("%lld", &v[j][i]);

    for (int j = 0; j <= n; j++)
        memo[n&1][j] = inf*(!!j);

    for (int i = n-1; i >= 0; i--) {
        for (int j = 0; j <= n; j++) {
            ll & me = memo[i&1][j];

            int x = j;
            int y = j+(i>e)-(i>s);

            me = inf;
            
            if (x == 0 && y == 0 && i) {
                continue;
            }

            for (int mask = 0; mask < 4; mask++) {
                int mj = j;

                ll loc = 0;

                // de onde vem
                if (i != s) {
                    if (mask&1) { // direita
                        if (y == n) continue;
                        loc += v[i][2] - v[i][0];
                    } else { // esquerda
                        if (x == 0) continue;
                        loc += v[i][1] + v[i][0];
                        mj--;
                    }
                }

                // pra onde vai
                if (i != e) {
                    if (mask&2) { // direita
                        if (x == n) continue;
                        loc += v[i][4] - v[i][0];
                        mj++;
                    } else { // esquerda
                        if (y == 0) continue;
                        loc += v[i][3] + v[i][0];
                    }
                }

                me = min(me, loc + memo[!(i&1)][mj]);
            }
        }
    }

    printf("%lld\n", memo[0][0]);
}
