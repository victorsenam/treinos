#include <bits/stdc++.h>
#define debug if (1)

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back
#define v first
#define f second

const int N = 1e3+7;

int n, m;
vector<pii> adj[N];
int edg[int(2e5)][2];

int ds[N][N][2], fr[N][N][2];

int main () {
    while (scanf("%d %d", &n, &m) != EOF) {
        for (int i = 0; i < n; i++)
            adj[i].clear();

        for (int i = 0; i < m; i++) {
            int a, b;
            scanf("%d %d", &a, &b);
            a--; b--;
            edg[i][0] = a; edg[i][1] = b;
            adj[a].pb(pii(b,i));
        }

        queue<pii> qu;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                fr[i][j][0] = fr[i][j][1] = n;
                ds[i][j][0] = ds[i][j][1] = N;
            }
            fr[i][i][0] = fr[i][i][1] = i;
            ds[i][i][0] = ds[i][i][1] = 0;

            for (pii & ed : adj[i]) {
                ds[i][ed.v][1] = 1;
                fr[i][ed.v][1] = ed.v;
                qu.push(pii(ed.v,1));
            }

            while (!qu.empty()) {
                pii & nd = qu.front();
                qu.pop();

                for (pii & ed : adj[nd.v]) {
                    if (ed.v == i) continue;
                    if (nd.f) {
                        if (ds[i][ed.v][1] > ds[i][nd.v][1] + 1) {
                            ds[i][ed.v][1] = ds[i][nd.v][1] + 1;
                            fr[i][ed.v][1] = fr[i][nd.v][1];
                            qu.push(pii(ed.v,1));
                        } else if (ds[i][ed.v][0] > ds[i][nd.v][1] + 1 && fr[i][ed.v][1] != fr[i][nd.v][1]) {
                            ds[i][ed.v][0] = ds[i][nd.v][1] + 1;
                            fr[i][ed.v][0] = fr[i][nd.v][1];
                            qu.push(pii(ed.v,0));
                        }
                    } else {
                        if (ds[i][ed.v][0] > ds[i][nd.v][0] + 1 && fr[i][ed.v][1] != fr[i][nd.v][0]) {
                            ds[i][ed.v][0] = ds[i][nd.v][0] + 1;
                            fr[i][ed.v][0] = fr[i][nd.v][0];
                            qu.push(pii(ed.v,0));
                        }
                    }
                }
            }
        }

        for (int i = 0; i < m; i++) {
            if (ds[edg[i][0]][edg[i][1]][0] == N)
                ds[edg[i][0]][edg[i][1]][0] = 0;
            printf("%d ", ds[edg[i][0]][edg[i][1]][0]);
        }
        putchar('\n');
    }
}
