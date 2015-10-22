#include <bits/stdc++.h>

using namespace std;

const int N = 53;

int visi[N][N];
int turn;
int memo[N][N];
int p[N];
int l, n;

int pd (int i, int j) {
    if (i+1 == j)
        return 0;

    if (visi[i][j] == turn)
        return memo[i][j];
    visi[i][j] = turn;

    memo[i][j] = INT_MAX;
    for (int k = i+1; k < j; k++)
        memo[i][j] = min(memo[i][j], max(max(pd(i, k), pd(k, j)), pd(i,k)+pd(k,j)+p[j]-p[i]));
    return memo[i][j];
}

int main( ){
    while (scanf("%d %d", &l, &n) != EOF && l) {
        p[0] = 0;
        for (int i = 1; i <= n; i++)
            scanf("%d", p+i);
        p[n+1] = l;
        
        turn++;
        printf("The minimum cutting is %d.\n", pd(0, n+1));
    }
}
