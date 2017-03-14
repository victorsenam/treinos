#include <bits/stdc++.h>

using namespace std;

#define N 102

int memo[N][N];
int n, k, v[N], t;

int pd (int i, int j) {
    if (i == j-1)
        return 1;
    if (i >= j)
        return 0;
    if (memo[i][j] != -1)
        return memo[i][j];

    int m = pd(i+1, j)+1;
    int res = 1;
    int ind = i+1;
    int last = i+1;

    while (ind < j) {
        if (v[ind] == v[i]) {
            res += pd(last, ind);
            last = ind+1;
            m = min(res+pd(last, j), m);
        }
        ind++;
    }

    memo[i][j] = m;
    return memo[i][j];
}

int main () {
    scanf("%d", &t);
    for (int c = 1; c <= t; c++) {
        scanf("%d %d", &n, &k);
        for (int i = 0; i <= n; i++) {
            if (i) scanf("%d", v+i-1);
            for (int j = 0; j <= n; j++)
                memo[i][j] = -1;
        }

        printf("Case %d: %d\n", c, pd(0, n));
    }
}
