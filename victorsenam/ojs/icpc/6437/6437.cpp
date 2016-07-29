#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 40007;
int uf[N], wf[N];
int n, m, k;
int ed[N][3];
int ts;
int p[N];

bool cmp_t (int i, int j) {
    for (int k = 2; k >= 0; k--)
        if (ed[i][k] != ed[j][k])
            return ed[i][k] < ed[j][k];
    return 0;
}

int find (int i) {
    if (uf[i] == i) return i;
    return uf[i] = find(uf[i]);
}

bool join (int i, int j) {
    if ((i = find(i)) == (j = find(j))) return 0;
    if (wf[i] < wf[j]) swap(i, j);
    wf[i] += wf[j];
    uf[j] = i;
    return 1;
}

int main () {
    scanf("%d", &ts);

    for (int tc = 1; tc <= ts; tc++) {
        scanf("%d %d %d", &n, &m, &k);

        ll res = 0;

        for (int i = 0; i <= n; i++) {
            uf[i] = i;
            wf[i] = 1;
        }

        for (int i = 0; i < k; i++) {
            int a;
            scanf("%d", &a);
            join(0, a);
        }

        for (int i = 0; i < m; i++) {
            p[i] = i;
            for (int k = 0; k < 3; k++)
                scanf("%d", &ed[i][k]);
        }

        sort(p, p+m, cmp_t);

        for (int it = 0; it < m; it++) {
            int i = p[it];

            if (join(ed[i][0], ed[i][1]))
                res += ed[i][2];
        }
        printf("Case #%d: %lld\n", tc, res);
    }
}
