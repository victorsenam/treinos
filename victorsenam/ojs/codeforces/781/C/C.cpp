#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 1e6+7;

int uf[N], wf[N];
int n, m, k;
int hd[N], nx[N], to[N], es;
vector<int> rs;
int cr;

int find (int u) {
    if (uf[u] == u) return u;
    return uf[u] = find(uf[u]);
}

int join (int u, int v) {
    if ((u = find(u)) == (v = find(v))) return 0;
    if (wf[u] < wf[v]) swap(u, v);
    wf[u] += wf[v];
    uf[v] = u;
    return 1;
}

int go (int u, int fr) {
    //printf("%d\n", u+1);
    for (int ed = hd[u]; ed; ed = nx[ed]) {
        if (to[ed] != fr) {
            rs.push_back(u);
            go(to[ed], u);
        }
    }
    rs.push_back(u);
}

int main () {
    scanf("%d %d %d", &n, &m, &k);

    for (int i = 0; i < n; i++) {
        uf[i] = i;
        wf[i] = 1;
    }

    es = 2;
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;

        if (join(a,b)) {
            //debug("%d %d\n", a+1, b+1);
            to[es] = b; nx[es] = hd[a]; hd[a] = es++;
            to[es] = a; nx[es] = hd[b]; hd[b] = es++;
        }
    }

    go(0,-1);

    int s = rs.size();
    int l = 0;
    for (int i = 0; i < k; i++) {
        int qt = (s/k) + (i < s%k);

        printf("%d", qt);
        for (int j = l; j < l + qt; j++)
            printf(" %d", rs[j]+1);
        printf("\n");
        l += qt;
    }
}
