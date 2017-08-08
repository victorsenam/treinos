#include <bits/stdc++.h>
#define debug if (1)

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e3+7;
const int M = 2e5+7;

int n, m;
vector<int> adj[N];
int edg[M][3];
int ds[N][N][2], fr[N][N][2];

int main () {
    while (scanf("%d %d", &n, &m) != EOF) {
        for (int i = 0; i < n; i++)
            adj[i].clear();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < 2; j++) {
                scanf("%d", &edg[i][j]);
                edg[i][j]--;
            }

            adj[edg[i][0]].pb(edg[i][1]);
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                for (int k = 0; k < 2; k++) {
                    ds[i][j][k] = N;
                    fr[i][j][k] = n;
                }
            
            queue<pii> qu;
            for (int v : adj[i]) {
                qu.push(pii(v,1));
                ds[i][v][1] = 1;
                fr[i][v][1] = v;
            }

            while (!qu.empty()) {
                int u = qu.front().first;
                int ty = qu.front().second;
                qu.pop();

                for (int v : adj[u]) {
                    if (v == i) continue;
                    if (ty) {
                        if (ds[i][v][1] > ds[i][u][1] + 1) {
                            ds[i][v][1] = ds[i][u][1] + 1;
                            fr[i][v][1] = fr[i][u][1];
                            qu.push(pii(v,1));
                        } else if (ds[i][v][0] > ds[i][u][1] + 1 && fr[i][v][1] != fr[i][u][1]) {
                            ds[i][v][0] = ds[i][u][1] + 1;
                            fr[i][v][0] = fr[i][u][1];
                            qu.push(pii(v,0));
                        }
                    } else {
                        if (ds[i][v][0] > ds[i][u][0] + 1) {
                            ds[i][v][0] = ds[i][u][0] + 1;
                            fr[i][v][0] = fr[i][u][0];
                            qu.push(pii(v,0));
                        }
                    }
                }
            }
        }

        for (int i = 0; i < m; i++) {
            int d = 0;
            if (ds[edg[i][0]][edg[i][1]][0] != N)
                d = ds[edg[i][0]][edg[i][1]][0];
            printf("%d ", d);
        }
        printf("\n");
    }
    
}
