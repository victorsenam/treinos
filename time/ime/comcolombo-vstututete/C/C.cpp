#include <bits/stdc++.h>

using namespace std;

const int N = 1001;
const int K = 11;
const int E = 51;
const int L = 4;
const int p[L] = {0, 4, 8, 11};
const int INF = 100000;

int memo[N][K][E][L];
int visi[N][K][E][L];
int s[N];
int n, ch, en;
int turn;

int pd (int i, int k, int e, int l) {
    if ( i == n ) return 0;
    
    int & me = memo[i][k][e][l];
    if (visi[i][k][e][l] == turn)
        return me;

    visi[i][k][e][l] = turn;

    me = INF;
    if (l <= e)
        me = min(me, pd(i+1, k, e-l, l) + max(s[i]-p[l], 0));
    else
        me = min(me, pd(i+1, 0, 0, 0) + s[i]);

    if (k <= 0)
        return me;

    for (int j = 0; j < 4; j++) {
        if (j > e)
            break;
        if (l == j)
            continue;
        me = min(me, pd(i+1, k-1, e-j, j)+max(s[i]-p[j], 0));
    }
    return me;
}

int main ( ) {
    int t;
    scanf("%d", &t);

    for (int ts = 1; ts <= t; ts++){
        scanf("%d %d %d", &n, &ch, &en);
        for (int i = 0; i < n; i++)
            scanf("%d", s+i);
        
        turn++;
        int ans = pd(0, ch, en, 0);

        printf("Case #%d: %d\n", ts, ans);

    }
}
