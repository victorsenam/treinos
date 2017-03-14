#include <bits/stdc++.h>

using namespace std;

#define N 50000
#define K 500

unsigned int d[N][K+1];
vector<unsigned int> g[N];
bool s[N];
int n, k, a, b, root, p;

long long int  contaPares (int v) {
    long long int r = 0, comb = 0;
    if (s[v]) return 0;
    d[v][0] = 1;
    s[v] = 1;

    for (vector<unsigned int>::iterator it = g[v].begin(); it != g[v].end(); it++) {
        r += contaPares(*it);
        for (int i = 0; !s[*it] && i < k && d[*it][i]; i++) d[v][i+1] += d[*it][i];
    }

    for (vector<unsigned int>::iterator it = g[v].begin(); it != g[v].end(); it++) {
        if (s[*it]) continue;

 /*
        printf("%d : ", v+1);
        for (int i = 0; i <= k; i++) printf("%d ", d[*it][i]);
        printf("\n");
*/

        for (int i = 0; i <= k-2; i++) {
  //          printf("%d : %d[%d]*(%d[%d]-%d[%d]) = %d\n", v+1, *it+1, i, v+1, k-1-i, *it+1, k-2-i, d[*it][i]*(d[v][k-1-i] - d[*it][k-2-i]));
            comb += d[*it][i]*(d[v][k-1-i] - d[*it][k-2-i]);
        }
    }

    r += d[v][k];
    r += comb/2;
    s[v] = 0;

    return r;
}

int main () {
    scanf("%d %d", &n, &k);

    for (int i = 0; i < n; i++) {
        s[i] = 0;
        for (int j = 0; j <= k; j++) d[i][j] = 0;

        if (i) {
            scanf("%d %d", &a, &b);

            g[--a].push_back(--b);
            g[b].push_back(a);
        }
    }

    printf("%I64d\n", contaPares(root));
}
