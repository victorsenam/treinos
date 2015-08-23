#include <bits/stdc++.h>

using namespace std;

const int N = 1000007;

vector<int> adj[N];
int deg[N];
queue<int> q;
int sol[N];
int n, m, a, b;

int main () {
    while (scanf("%d %d", &n, &m) != EOF && (n || m)) {
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            deg[i] = 0;
        }
        while (!q.empty()) q.pop();

        for (int i = 0; i < m; i++) {
            scanf("%d %d", &a, &b);
            a--; b--;
            adj[a].push_back(b);
            deg[b]++;
        }

        for (int i = 0; i < n; i++)
            if (deg[i] == 0)
                q.push(i);

        b = 0;
        while (!q.empty()) {
            a = q.front();
            q.pop();
            
            sol[b++] = a;

            for (int i = 0; i < adj[a].size(); i++) {
                deg[adj[a][i]]--;
                if (deg[adj[a][i]] == 0)
                    q.push(adj[a][i]);
            }
        }

        if (b == n) {
            for (int i = 0; i < n; i++)
                printf("%d\n", sol[i]+1);
        } else 
            printf("IMPOSSIBLE\n");
    }
}
