#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long int num;

int turn;
int vis[2][66][66];
num memo[2][66][66];
int val[63];
num n, nx;
int k;
num res;

num pd (bool free, int pos, int qtd) {
    if (qtd == 0) return 1;
    if (pos < 0) return 0;

    if (free) {
        if (!vis[free][pos][qtd])
            memo[free][pos][qtd] = pd(1, pos-1, qtd) + pd(1, pos-1, qtd-1);
    } else {
        if (vis[free][pos][qtd] != turn) {
            if ((n&(1llu<<pos)))
                memo[free][pos][qtd] = pd(1, pos-1, qtd) + pd(0, pos-1, qtd-1);
            else
                memo[free][pos][qtd] = pd(0, pos-1, qtd);
        }
    }

    vis[free][pos][qtd] = turn;
    
    return memo[free][pos][qtd];
}

int main () {
    val[0] = val[1] = 0;
    for (int i = 2; i < 65; i++) {
        int cnt = __builtin_popcount(i);
        val[i] = val[cnt]+1;
    }
    memset(memo, 0, sizeof(memo));
    memset(vis, 0, sizeof(vis));
    turn = 0;

    while (scanf("%llu %llu %d", &nx, &n, &k) != EOF && (n || nx || k)) {
        if (k == 0) {
            if (nx > 1)
                printf("0\n");
            else
                printf("1\n");
            continue;
        }

        turn++;
        res = 0;
        for (int i = 1; i < 64; i++) {
            if (val[i] == k-1) {
 //               printf("%llu on %d(%d) -> %llu\n", n, i, val[i], pd(0, 61, i));
                res += pd(0, 63, i);
            }
        }

        turn++;
        n = nx-1;
        for (int i = 1; i < 64; i++) {
            if (val[i] == k-1) {
                //printf("%llu on %d(%d) -> %llu\n", n, i, val[i], pd(0, 61, i));
                res -= pd(0, 63, i);
            }
        }

        if (k == 1 && res > 0 && n == 0)
            res--;

        printf("%llu\n", res);
    }
}
