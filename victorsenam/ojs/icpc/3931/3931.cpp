#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 107;

char emm[N][N];
char str[N];
int nx[N];
int n,m;

ll visi[N][N+1], turn;
ll memo[N][N+1];

ll pd (int i, int lm) {
    if (i >= lm) return INT_MAX;
    if (!str[i]) return 0;
    lm = min(lm, nx[i]);

    ll & me = memo[i][lm];
    if (visi[i][lm] == turn) return me;
    visi[i][lm] = turn;

    return me = min(pd(i+1, lm), pd(i+1, N)+1ll);
}

void preproc (char att[]) {
    int j;
    for (int i = 0; str[i]; i++) {
        for (j = 0; att[j] && str[i+j] && str[i+j] == att[j]; j++);
        if (!att[j])
            nx[i] = min(nx[i], i+j);
    }
}

int main () {
    while (scanf("%d %d", &n, &m) != EOF && (n||m)) {
        for (int i = 0; i < n; i++) {
            scanf(" %[^\n ]", emm[i]);
        }

        ll res = 0;
        for (int i = 0; i < m; i++) {
            scanf(" %[^\n]", str);

            for (int j = 0; !j || str[j-1]; j++)
                nx[j] = N;

            for (int j = 0; j < n; j++)
                preproc(emm[j]);

            turn++;
            res += pd(0, N);
        }

        printf("%lld\n", res);
    }
}
