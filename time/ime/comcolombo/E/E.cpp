#include <bits/stdc++.h>

using namespace std;

const int N = 501;
const int M = N*N;

int n, m;
int ss;
int t[N];
int adj[N][N];
vector<int> gra[N];
int in[N];
int ts;
int a, b;
int sol[N];

int main () {
    scanf("%d", &ts);

    while (ts--) {
        queue<int> q;
        scanf("%d", &n);
        memset(adj, 0, sizeof adj);
        for (int i = 0; i < n; i++) {
            gra[i].clear();
            scanf("%d", t+i);
            t[i]--;
            in[i] = 0;
            for (int j = 0; j < i; j++)
                adj[t[j]][t[i]] = 1;
        }

        scanf("%d", &m);
        for (int i = 0; i < m; i++) {
            scanf("%d %d", &a, &b);
            a--; b--;
            swap(adj[a][b], adj[b][a]);
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (adj[i][j]) {
                    gra[i].push_back(j);
                    in[j]++;
                }
            }
        }

        for (int i = 0; i < n; i++)
            if (in[i] == 0)
                q.push(i);

        ss = 0;
        while (!q.empty()) {
            if (q.size() > 1) {
                int rm = 0;
                int ob = q.size();
                printf("deu ruim\n");
                while (rm < ob) {
                    int a = q.front();
                    q.pop();
                    rm++;
                    sol[ss++] = -1;

                    for (int j = 0; j < gra[a].size(); j++) {
                        in[gra[a][j]]--;
                        if (in[gra[a][j]] == 0)
                            q.push(gra[a][j]);
                    }
                }
            } else {
                int a = q.front();
                q.pop();

                sol[ss++] = a;

                for (int j = 0; j < gra[a].size(); j++) {
                    in[gra[a][j]]--;
                    if (in[gra[a][j]] == 0)
                        q.push(gra[a][j]);
                }
            }            
        }
        
        if (ss < n) {
            printf("IMPOSSIBLE\n");
        } else {
            for (int i = 0 ;i < ss; i++) {
                if (i)
                    printf(" ");
                if (sol[i] == -1)
                    printf("?");
                else
                    printf("%d", sol[i]+1);
            }
            printf("\n");
        }
    }
}
