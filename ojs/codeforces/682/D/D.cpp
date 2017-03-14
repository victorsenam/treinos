#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#define lld I64d
#endif

const int N = 1007;
const int M = 12;

int n, m, k;
int memo[N][N][M][2];
int visi[N][N][M][2];
char str[2][N];

int pd (int i, int j, int k, bool s) {
    if (i == n || j == m || k < 0) {
        if (k == 0)
            return 0;
        return -10000;
    }

    int & me = memo[i][j][k][s];
    if (visi[i][j][k][s])
        return me;
    visi[i][j][k][s] = 1;

    me = pd(i+1, j, k, 0);
    me = max(me, pd(i, j+1, k, 0));
    if (str[0][i] == str[1][j]) {
        me = max(me, pd(i+1, j+1, k-1, 1) + 1);
        if (s) 
            me = max(me, pd(i+1, j+1, k, 1) + 1);
    }

    return me;
}

int main () {
    scanf("%d %d %d", &n, &m, &k);
    
    for (int i = 0; i < 2; i++)
        scanf(" %s", str[i]);
    printf("%d\n", pd(0, 0, k, 0));
}
