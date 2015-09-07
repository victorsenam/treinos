#include <bits/stdc++.h>

using namespace std;

const int N = 107;
const int K = 100;

int sol[N][N];
int res[N][N];
int vis[N][N];
int cor[N];
int n;
int turn;

int pd (int i, int j) {
    if (vis[i][j] == turn)
        return res[i][j];
    vis[i][j] = turn;

    int & me = res[i][j];

    if (i == j) {
        me = 0;
        sol[i][j] = cor[i];
        return me;
    }
    
    pd(i+1, j);
    sol[i][j] = (sol[i+1][j] + cor[i])%K;
    
    me = INT_MAX;
    for (int k = i; k < j; k++)
        me = min(me, pd(i, k) + pd(k+1, j) + sol[i][k]*sol[k+1][j]);
    return me;
}

int main () {
    while (scanf("%d", &n) != EOF) {
        for (int i = 0; i < n; i++)
            scanf("%d", cor+i);
        turn++;
        printf("%d\n", pd(0, n-1));
    }
}
