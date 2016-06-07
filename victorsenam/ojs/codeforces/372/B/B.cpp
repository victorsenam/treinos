#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define LLD "%lld"
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define LLD "%I64d"
#define DEBUG(...) {}
#endif

const int N = 42;

int acc[N][N];
char mat[N][N];
int memo[N][N][N][N];
int n, m, q;
int a, b, c, d;

bool isret (int a, int b, int c, int d) {
    bool r = !(acc[c][d]-acc[a-1][d]-acc[c][b-1]+acc[a-1][b-1]);
    return r;
}

int pd (int a, int b, int c, int d) {
    if (a > c || b > d) return 0;

    int & me = memo[a][b][c][d];
    if (me != -1)
        return me;

    me = isret(a, b, c, d);

    for (int i = 1; i < (1<<4); i++) {
        int loc = pd(a+!!(i&1), b+!!(i&2), c-!!(i&4), d-!!(i&8));
        if (__builtin_popcount(i)%2)
            me += loc;
        else
            me -= loc;
    }

    return me;
}

int main () {
    memset(memo, -1, sizeof memo);
    scanf("%d %d %d", &n, &m, &q);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf(" %c", &mat[i][j]);
            mat[i][j] -= '0';
            acc[i][j] = acc[i-1][j] + acc[i][j-1] - acc[i-1][j-1] + mat[i][j];
        }
    }

    for (int i = 0; i < q; i++) {
        scanf("%d %d %d %d", &a, &b, &c, &d);
        printf("%d\n", pd(a, b, c, d));
    }
}
