#include <bits/stdc++.h>

using namespace std;

const int N = 103;

int uf[N], wf[N];
int n, m;
int p[N];
int deg[N];
int maxi[N], mini[N], sum[N], cnt[N];

int find (int i) {
    if (i == uf[i])
        return i;
    return uf[i] = find(uf[i]);
}

void join (int i, int j) {
    i = find(i); j = find(j);
    if (i == j)
        return;
    if (wf[i] < wf[j])
        swap(i, j);
    wf[i] += wf[j];
    uf[j] = i;
}

int main () {
    int t;
    scanf("%d", &t);
    for (int ts = 1; ts <= t; ++ts) {
        scanf("%d %d", &n, &m);

        for (int i = 0; i < n; i++){
            uf[i] = i;
            wf[i] = 1;
            maxi[i] = mini[i] = sum[i] = cnt[i] = 0;
            mini[i] = INT_MAX;
            deg[i] = 0;
        }

        for (int i = 0; i < m; i++) {
            int a, b;
            scanf("%d %d", &a, &b);
            a--; b--;
            join(a, b);
            deg[a]++;
            deg[b]++;
        }

        for (int i = 0; i < n; i++) {
            int aux = find(i);
            maxi[aux] = max(maxi[aux], deg[i]);
            mini[aux] = min(mini[aux], deg[i]);
            sum[aux] += deg[i];
            cnt[aux]++;
        }

        int res = 0;
        for (int i = 0; i < n; i++) {
            if (cnt[i] == 2)
                res++;
            if (cnt[i] == 0 || cnt[i]%2)
                continue;
            if (maxi[i] != cnt[i]/2 || mini[i] != cnt[i]/2-1)
                continue;
            if (sum[i] != cnt[i]*(cnt[i]/2-1)+2)
                continue;
            res++;
        }
        printf("Case #%d: %d\n", ts, res);
    }
}
