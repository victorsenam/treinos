#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define debug(...) {}
#endif

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 1e6+8;

int uf[N], wf[N];
int n;
int a[N];
map<int, vector<int> > mp;

int find (int u) {
    if (u == uf[u]) return u;
    return uf[u] = find(uf[u]);
}

void join (int u, int v) {
    if ((u = find(u)) == (v = find(v))) return;
    if (wf[u] < wf[v]) swap(u, v);
    uf[v] = u;
    wf[u] += wf[v];
}

int main () {
    while (scanf("%d", &n) != EOF && n) {
        mp.clear();
        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
            uf[i] = i;
            wf[i] = 1;

            int p = i - a[i];
            for (int x : mp[p]) {
                join(x, i);
            }

            p = i + a[i];
            mp[p].push_back(i);
        }

        for (int i = n-1; i >= 0; i--) {
            if (find(i) == find(0)) {
                printf("%d\n", i);
                break;
            }
        }
    }
}
