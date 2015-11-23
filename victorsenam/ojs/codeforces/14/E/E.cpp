#include <bits/stdc++.h>

using namespace std;

const int N = 30;
typedef long long int num;

num memo[N][N][2][N];

int n, t;

num pd (int i, int p, bool up, int t) {
    if (t < 0)
        return 0;
    if (i == n)
        return ((t==0) && !up);
    
    num & me = memo[i][p][up][t];
    if (me != -1)
        return me;
    me = 0;

    for (int h = 1; h < p; h++) {
        me += pd(i+1, h, 0, t-up);
    }

    for (int h = p+1; h <= 4; h++) {
        me += pd(i+1, h, 1, t);
    }

    return me;
}

int main ( ) {
    scanf("%d %d", &n, &t);
    memset(memo, -1, sizeof memo);

    num ans = 0;
    for (int i = 1; i <= 4; i++) {
        for (int j = i+1; j <= 4; j++) {
            ans += pd(2, j, 1, t);
        }
    }
    printf("%I64d\n", ans);
}

