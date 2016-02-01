#include <bits/stdc++.h>

using namespace std;

const int N = 1000007;
const int K = 5;
const int INF = INT_MAX-N;

int memo[N][K][K];
int visi[N][K][K];
int turn;
int n, t;
int d[N];

int pd (int i, int k, int g) {
    if (k == 4) {
        if (g && ((d[i]+g > 100) || k == g))
            return INF;
        return pd(i, 0, 0);
    }
    if (i == n) {
        if (k == 0)
            return 0;
        if (d[i-1]+4-k > 100)
            return INF;
        return 4-k;
    }

    int & me = memo[i][k][g];
    if (visi[i][k][g] == turn)
        return me;
    visi[i][k][g] = turn;

    me = pd(i, k+1, g+1)+1;

    if (k) {
        bool cond = 1;
        if (k == g) {
            cond = (cond && d[i] > g);
        } else {
            cond = (cond && d[i]-d[i-1] > g);
            cond = (cond && d[i]-d[i-1] <= 10*(g+1));
        }

        if (cond)
            me = min(me, pd(i+1, k+1, 0));
    } else {
        me = min(me, pd(i+1, k+1, 0));
    }

    return me;
}

int main () {
    scanf("%d", &t);
    int ts = 0;

    while (t--) {
        turn+=2;
        scanf("%d", &n);

        for (int i = 0; i < n; i++)
            scanf("%d", d+i);

        printf("Case #%d: %d\n", ++ts, pd(0, 0, 0));
    }
}
