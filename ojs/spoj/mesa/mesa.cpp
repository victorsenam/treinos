#include <bits/stdc++.h>

using namespace std;

#define N 100

int n, m, a, b;
vector<int> adj[N];
bool cols[N];
bool v[N];
queue<int> q;

int main () {
    int t = 0;
    while (scanf("%d %d", &n, &m) != EOF) {
        t++;
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            v[i] = 0;
        }
        for (int i = 0; i < m; i++) {
            scanf("%d %d", &a, &b);
            adj[a-1].push_back(b-1);
            adj[b-1].push_back(a-1);
        }
        while (!q.empty()) q.pop();

        bool ok = 1;
        for (int i = 0; i < n && ok; i++) {
            if (v[i]) continue;

            cols[i] = v[i] = 1;
            q.push(i);

            while (!q.empty() && ok) {
                a = q.front();
                //printf("%d %d\n", a, cols[a]);
                q.pop();

                for (int j = 0; j < adj[a].size() && ok; j++) {
                    if (v[adj[a][j]]) {
                        if (cols[a] == cols[adj[a][j]]) {
                            ok = 0;
                        }
                    } else {
                        v[adj[a][j]] = 1;
                        cols[adj[a][j]] = !cols[a];
                        q.push(adj[a][j]);
                    }
                }
            }
        }

        printf("Instancia %d\n", t);
        if (ok) printf("sim\n");
        else printf("nao\n");
        printf("\n");
    }
}
