#include <bits/stdc++.h>

using namespace std;

const int N = 100007;

vector<int> adj[N];
int deg[N];
int t, n, a, b, ss;
queue<pair<int, int> > q;
pair<int, int> aux;

int main () {
    scanf("%d", &t);

    while (t--) {
        scanf("%d", &n);
        if (n == 1) {
            printf("0\n");
            continue;
        }
        
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            deg[i] = 0;
        }
        for (int i = 0; i < n-1; i++) {
            scanf("%d %d", &a, &b);
            adj[a].push_back(b);
            adj[b].push_back(a);
            deg[a]++;
            deg[b]++;
        }
    
        ss = -1;
        int cnt = 0;

        for (int i = 0; i < n; i++) {
            if (deg[i] == 1)
                q.push(make_pair(i, 0));
        }

        while (!q.empty()) {
            aux = q.front();
            if (ss == aux.second)
                cnt++;
            else if (ss < aux.second) {
                cnt = 0;
                ss = aux.second;
            }
            deg[aux.first] = 0;
            for (int i = 0; i < adj[aux.first].size(); i++) {
                deg[adj[aux.first][i]]--;
                if (deg[adj[aux.first][i]] == 1) {
                    q.push(make_pair(adj[aux.first][i], aux.second+1));
                }
            }
            q.pop();
        }

        printf("%d\n", ss+cnt);
    }
}
