#include <bits/stdc++.h>

using namespace std;

const int N = 10007;

queue<int> q;
bool inc;
int t, n, m, ss, a, b;
vector<int> adj[N];
int deg[N], sol[N];

int main () {
    scanf("%d", &t);
    
    while (t--) {
        scanf("%d %d", &n, &m);

        for (int i = 0; i < n; i++) {
            adj[i].clear();
            deg[i] = 0;
        }
        
        ss = 0;

        for (int i = 0; i < m; i++) {
            scanf("%d %d", &a, &b);
            a--;
            b--;
            adj[a].push_back(b);
            deg[b]++;
        }

        while (!q.empty()) q.pop();

        for (int i = 0; i < n; i++)
            if (!deg[i])
                q.push(i);

        inc = 0;
        while (!q.empty() && ss < n) {
            if (q.size() > 1)
                inc = 1;
            
            a = q.front();
            q.pop();

            sol[ss++] = a;

            for (int i = 0; i < adj[a].size(); i++) {
                deg[adj[a][i]]--;
                if (deg[adj[a][i]] == 0)
                    q.push(adj[a][i]);
            }
        }

        if (ss < n)
            printf("recheck hints\n");
        else if (inc)
            printf("missing hints\n");
        else {
            for (int i = 0; i < n; i++)
                printf("%d ", sol[i]+1);
            printf("\n");
        }
    }
}
