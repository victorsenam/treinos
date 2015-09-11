#include <bits/stdc++.h>

using namespace std;

const int mi[4] = {0, 0, 1, -1};
const int mj[4] = {1, -1, 0, 0};

const int N = 23;
const int T = 1003;

int memo[N][N][T];
int tap[N][N][T];
int n, x, y, z;

int pd (int i, int j, int t) {
    if (t >= 1001)
        return 0;
    if (i < 0 || i > 20)
        return 0;
    if (j < 0 || j > 20)
        return 0;

    int & me = memo[i][j][t];
    if (me != -1)
        return me;

    me = pd(i, j, t+1);
    for (int k = 0; k < 4; k++)
        me = max(me, pd(i+mi[k], j+mj[k], t+1));
    me += tap[i][j][t];
    return me;
}

int main () {
    scanf("%d", &n);

    memset(memo, -1, sizeof memo);

    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &x, &y, &z);
        tap[x][y][z]++;
    }

    printf("%d\n", pd(6,6,0));
}
