#include <bits/stdc++.h>

using namespace std;

const int M = 7;
const int N = (1<<11);

int memo[2][M][N];
int visi[2][M][N], turn;
int a, b;
char s[M];
int n;

int pd (bool pre, int i, int mask) {
    if (i == n) return 1;
    int & me = memo[pre][i][mask];

    if (visi[pre][i][mask] == turn) return me;
    visi[pre][i][mask] = turn;
    me = 0;

    for (int k = 0; k <= (pre?9:s[i]-'0'); k++)
        me += (
            (mask&(1<<k)) ? 0 : pd(
                ( pre || (k<s[i]-'0') ),
                i+1,
                (!(mask||k)?0:( mask | (1<<k) ))
            )
        );
    return me;
}

int main () {
    while (scanf(" %d %d", &a, &b) != EOF) {
        ++turn;
        sprintf(s, "%06d", b);
        n = strlen(s);
        int res = pd(0,0,0);

        ++turn;
        sprintf(s, "%06d", a-1);
        n = strlen(s);
        res -= pd(0,0,0);
        printf("%d\n", res);
    }

}
