#include <bits/stdc++.h>

using namespace std;

const int N = 200008;

typedef unsigned long long int num;
num a[N];
num sl[N], sr[N];
int n, k;
num x;
num memo[N][11];
int vis[N][11];
int turn;

num pd(int i, int k) {
    if (i == n)
        return 0llu;

    num me = memo[i][k];
    if (vis[i][k] == turn)
        return me;
    vis[i][k] = turn;

    me = pd(i+1, k)|a[i];
    num mp = 1llu;
    for (int j = 0; j < k; j++) {
        mp *= x;
        me = max(pd(i+1, k-j-1)|(a[i]*mp), me);
    }

    return me;
}

int main () {
    scanf("%d %d %I64u", &n, &k, &x);

    turn++;
    for (int i = 0; i < n; i++)
        scanf("%I64u", a+i);

    printf("%I64u\n", pd(0, k));
}
