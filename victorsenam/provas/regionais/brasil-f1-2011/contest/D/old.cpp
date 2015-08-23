#include <bits/stdc++.h>

using namespace std;

#define N 1000

int n, m, a, b, t, v0, v1;
int mycp;
bool comps[2][N];
int cntcp[2];
int cons;
vector<int> adj[N];

void dfs (int v, int cp) {
    if (comps[cp][v]) return;
    comps[cp][v] = 1;
    cntcp[cp]++;
    for (int i = 0; i < adj[v].size(); i++)
        dfs(adj[v][i], cp);
}

int main() {
    while (scanf("%d %d", &n, &m) != EOF) {
        for (int i = 0; i < n-1; i++) {
            adj[i].clear();
            comps[0][i] = comps[1][i] = 0;
        }
        cntcp[0] = cntcp[1] = 0;
        scanf("%d %d %d", &a, &b, &t);
        v0 = a-1;
        v1 = b-1;

        for (int i = 1; i < m; i++) {
            scanf("%d %d %d", &a, &b, &t);
            adj[a-1].push_back(b-1);
            if (t == 2) adj[b-1].push_back(a-1);
        }

        dfs(v0, 0);
        dfs(v1, 1);

        if (cntcp[0] == n && cntcp[1] == n) {
            printf("-\n");
            continue;
        }
        if (cntcp[0] + cntcp[1] <= n) {
            printf("*\n");
            continue;
        }
        
        cons = 0;
        for (int i = 0; i < n; i++) {
            if (comps[0][i] && comps[1][i]) continue;
            else if (comps[0][i]) mycp = 0;
            else mycp = 1;

            for (int j = 0; j < adj[i].size(); j++)
                if (comps[!mycp][adj[i][j]]) cons++;
        }

        if (cons == 0) printf("*\n");
        else if (cons == 1) printf("1\n");
        else printf("2\n");
    }
}
