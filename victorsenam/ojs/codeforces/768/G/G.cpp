#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 1e5+7;

int n;
int pr[N];
int dg[N], cn[N];

int sz[N];
int gtr[N], res[N], 

vector<int> adj[N];
multiset<int> ch_sz[N];
multiset<int> ch_sb[N];

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;
        pr[b] = a;
        adj[a].push_back(b);
        dg[a]++;
    }

    queue<int> qu;

    for (int i = 0; i < n; i++)
        if (!dg[i])
            qu.push(i);

    while (!qu.empty()) {
        int u = qu.front();
        qu.pop();

        sz[u]++;
        if (n-sz[u])
            ch_sz[u].insert(n-sz[u]);
        res[u] = *(ch_sz[u].rbegin());

        if (adj[u].size() > 1) {
            int mx = adj[u][0];
            for (int i = 1; i < adj[u].size(); i++)
                if (ch_sb[adj[u][i]].size() > ch_sb[mx].size())
                    mx = adj[u][i];

            ch_sz[u].erase(ch_sz[u].find(sz[mx]);
            int mv = ch_sz[u].rbegin();
            ch_sz[u].insert(sz[mx]);

            for (int i = 0; i < adj[u].size(); i++) {
                int v = adj[u][i];
                if (v == mx) continue;

                mv - 
                
            }

        }

        ch_sb[u].insert(sz[u]);

        if (pt[u] == -1)
            continue;

        sz[pr[u]] += sz[u];
        ch_sz[pr[u]].insert(sz[u]);

        cn[pr[u]]++;
        if (cn[pr[u]] = dg[pr[u]])
            qu.push(pr[u]);
    }

    for (int i = 0; i < n; i++)
        printf("%d\n", res[i]);
}
