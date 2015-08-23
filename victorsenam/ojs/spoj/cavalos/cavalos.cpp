#include <bits/stdc++.h>

using namespace std;

#define N 100

vector<int> adj[2*N+2];
int org[2*N+2], visi[2*N+2];
int n, m, k, a, b, c, turn, t;
queue<pair<int, int> > q;
int flow[2*N+2][2*N+2];

// 2*N+1 dest
// 2*N orig

int main () {
    t = 0;
    while (scanf("%d %d %d", &n, &m, &k) != EOF) {
        turn = -1;

        adj[2*N+1].clear();
        for (int i = 0; i < n; i++) {
            scanf("%d", &c);
            visi[i] = -1;
            adj[i].clear();

            adj[i].push_back(2*N+1);
            adj[2*N+1].push_back(i);
            
            flow[i][2*N+1] = c;
            flow[2*N+1][i] = 0;
        }

        adj[2*N].clear();
        for (int i = 0; i < m; i++) {
            visi[N+i] = -1;
            adj[N+i].clear();

            adj[2*N].push_back(N+i);
            adj[N+i].push_back(2*N);
            
            flow[2*N][N+i] = 1;
            flow[N+i][2*N] = 0;
        }
    
        visi[2*N] = visi[2*N+1] = -1;

        for (int i = 0; i < k; i++) {
            scanf("%d %d", &a, &b);
            adj[N+b-1].push_back(a-1);
            adj[a-1].push_back(N+b-1);

            flow[N+b-1][a-1] = 1;
            flow[a-1][N+b-1] = 0;
        }

        while (42) {
            q.push(make_pair(2*N+1, -1));
            turn++;
            while (!q.empty() && visi[2*N] < turn) {
                a = q.front().first;
                b = q.front().second;
                q.pop();
               // printf("%d\n", a);

                if (visi[a] >= turn) continue;
                visi[a] = turn;
                org[a] = b;


                for (int i = 0; i < adj[a].size(); i++) {
                    if (flow[adj[a][i]][a] == 0) continue;
                    q.push(make_pair(adj[a][i], a));
                }
            }
            while (!q.empty()) q.pop();
            if (visi[2*N] < turn) break;
            
            a = 2*N;
            c = INT_MAX;
            while (a != 2*N+1) {
                c = min(c, flow[a][org[a]]);
 //               printf("%d ", a);
                a = org[a];
            }
   //         printf("\n");

            a = 2*N;
            while (a != 2*N+1) {
                flow[a][org[a]] -= c;
                flow[org[a]][a] += c;
                a = org[a];
            }
        }

        c = 0;
        for (int i = 0; i < adj[2*N+1].size(); i++)
            c += flow[2*N+1][adj[2*N+1][i]];

        printf("Instancia %d\n", ++t);
        printf("%d\n\n", c);
    }
}
