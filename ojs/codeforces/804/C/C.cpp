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

const int N = 1e6+3;

int n, m;
int cs;
int c[N];
vector<int> v[N];
set<int> s;
set<int>::iterator it;
vector<int> adj[N];

int dfs (int u, int p) {
    for (int x : v[u])
        if (c[x])
            s.erase(c[x]); // se der RE tá errado tudo mesmo

    it = s.begin();
    for (int x : v[u]) {
        if (!c[x]) {
            c[x] = *it; // se der RE tá errado também
            cs = max(cs, c[x]);
            ++it;
        }
    }
    
    for (int x : v[u])
        s.insert(c[x]);

    for (int v : adj[u]) {
        if (v == p) continue;
        dfs(v, u);
    }
}

int main () {
    scanf("%d %d", &n, &m);

    int mx = 0;
    for (int i = 0; i < n; i++) {
        int q;
        scanf("%d",&q);
        mx = max(mx, q);

        for (int j = 0; j < q; j++) {
            int a ;
            scanf("%d", &a);
            v[i].push_back(a);
        }
    }

    for (int i = 1; i <= m; i++)
        s.insert(i);

    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(0, 0);
    assert(mx == cs);

    if (cs == 0)
        cs = 1;

    printf("%d\n", cs);
    for (int i = 1; i <= m; i++)
        printf("%d ", max(c[i], 1));
    printf("\n");

}
