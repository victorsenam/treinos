#include <bits/stdc++.h>

using namespace std;

const int N = 4;
const int M = 5;
typedef unsigned long long int num;

int n, m;
int x, y;
bool visi[M][M][(1llu<<(N*N))][2];
bool memo[M][M][(1llu<<(N*N))][2];

bool get (num mask, int i, int j) 
{ return (mask&((1llu<<j)<<(i*N))); }
num setb (num mask, int i, int j)
{ return (mask|((1llu<<j)<<(i*N))); }
num unset (num mask, int i, int j)
{ return (mask&(~((1llu<<j)<<(i*N)))); }

num remlastrow(num mask, int n) {
    for (int i = 0; i < N; i++)
        mask = unset(mask, n, i);
    return mask;
}
num remfirstrow (num mask)
{ return (mask>>(N-1)); }
num remlastcol (num mask, int m) {
    for (int i = 0; i < N; i++)
        mask = unset(mask, i, m);
}
num remfirstcol (num mask, int m)
{ return remlastcol((mask>>1), m); }

void printmask (num mask, int n, int m) {
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            printf("%d", get(mask, i, j));
            mask = unset(mask, i, j);
        }
    }
    assert(!mask);
}

bool dp (int n, int m, num mask, bool ty) {
    if (n == 0 && m == 0)
        return 1;

    if (visi[n][m][mask][ty])
        return memo[n][m][mask][ty];
    visi[n][m][mask][ty] = 1;

    bool & me = memo[n][m][mask][ty];
    me = !ty;

    num att;
    if (ty) {
        if (n) {
            if (!get(mask, 0, 0)) {
                att = remfirstrow(mask);
                me |= dp(n-1, m, att, 0);
            }

            if (!get(mask, n, m)) {
                att = remlastrow(mask, n);
                me |= dp(n-1, m, att, 0);
            }
        }

        if (m) {
            if (!get(mask, 0, 0)) {
                att = remfirstcol(mask, m);
                me |= dp(n, m-1, att, 0);
            }
            
            if (!get(mask, n, m)) {
                att = remlastcol(mask, m);
                me |= dp(n, m-1, att, 0);
            }
        }
    } else { 
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                if (!get(mask, i, j)) {
                    me &= dp(n, m, setb(mask, i, j), 1);
                }
            }
        }
    }

    printmask(mask, n, m);
    printf(" [%d] --> %d\n", ty, me);
    return me;
}

int main () {
    scanf("%d %d", &n, &m);
    scanf("%d %d", &n, &m);
    scanf("%d %d", &x, &y);

    n = abs(n-x);
    m = abs(m-y);

    if (max(n, m) > 4)
        printf("Second\n");
    else if (dp(n, m, 0llu, 1))
        printf("First\n");
    else
        printf("Second\n");
}
