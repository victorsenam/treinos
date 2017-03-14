#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long int num;

const int N = 6;

bool st[N][N];
//bool memo[N][N][(1<<22)][2];
//bool visi[N][N][(1<<22)][2];

int bt (int si, int sj, int n, int m, bool ty) {
    bool res = !ty;
    num mask = 0llu;

    if (n == si+1 && m == sj+1)
        return 1;

    //for (int i = si; i < n; i++)
    //    for (int j = sj; j < m; j++)
    //        mask = ((mask<<1)&(st[i][j]));

    //if (visi[n-si][m-sj][mask][ty])
    //    return memo[n-si][m-sj][mask][ty];
    //visi[n-si][m-sj][mask][ty] = 1;

    if (ty) {
        if (n > si+1) {
            if (!st[si][sj])
                res |= bt(si+1, sj, n, m, 0);
            if (!st[n-1][m-1])
                res |= bt(si, sj, n-1, m, 0);   
        }
        if (m > sj+1) {
            if (!st[si][sj])
                res |= bt(si, sj+1, n, m, 0);
            if (!st[n-1][m-1])
                res |= bt(si, sj, n, m-1, 0);
        }
    } else {
        for (int i = si; res && i < n; i++) {
            for (int j = sj; res && j < m; j++) {
                if (st[i][j] || (i == 0 && j == 0) || (i == n-1 && j == m-1))
                    continue;
                st[i][j] = 1;
                res &= bt(si, sj, n, m, 1);
                st[i][j] = 0;
            }
        }
    }

    // memo[n-si][m-sj][mask][ty] = res;
    return res;
}

int main () {
    int n, m;
    int x, y;

    scanf("%d %d", &n, &m);
    scanf("%d %d", &n, &m);
    scanf("%d %d", &x, &y);

    n -= x;
    m -= y;
    if (n < 0)
        n = -n;
    if (m < 0)
        m = -m;
    n++; m++;

    if ((n == m && n == 5) || max(n, m) > 5 || !bt(0, 0, n, m, 1))
        printf("Second\n");
    else
        printf("First\n");
}
