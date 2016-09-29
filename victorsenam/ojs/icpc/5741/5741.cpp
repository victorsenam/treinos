#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define debug(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 150008;
const int K = 307;

int hd[N], nx[N], to[N], es;
int n, k;
int memo[N][K];
int sib[N];
int ps;
int p[N];
int pr[N], wg[N];

void dfs (int u) {
    p[ps++] = u;
    for (int ed = hd[u]; ed; ed = nx[ed])
        dfs(to[ed]);
    sib[u] = ps;
}

int main () {
    while (scanf("%d %d", &n, &k) != EOF) {
        int rt = 0;
        ps = 0;
        es = 1;
        for (int i = 0; i < n; i++)
            hd[i] = 0;

        for (int i = 0; i < n; i++) {
            scanf("%d %d", pr+i, wg+i);
            pr[i]--;

            if (pr[i] != -1) {
                nx[es] = hd[pr[i]]; to[es] = i; hd[pr[i]] = es++;
            } else {
                rt = i;
            }
        }

        dfs(rt);

        for (int j = 1; j <= k; j++)
            memo[n][j] = -1;
        memo[n][0] = 0;

        for (int _i = n-1; _i >= 0; _i--) {
            int i = p[_i];
            for (int j = 1; j <= k; j++) {
                int & me = memo[_i][j];

                me = memo[_i+1][j];
                if (memo[sib[i]][j-1] >= 0)
                    me = max(memo[sib[i]][j-1] + wg[i], me);
            }
            memo[_i][0] = 0;
        }

        if (memo[0][k] == -1)
            printf("impossible\n");
        else
            printf("%d\n", memo[0][k]);
    }
}
