#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define debug(...) {}
#endif

using namespace std;
typedef long long int ll;
typedef pair<ll, ll> pii;
#define pb push_back

const int N = 127;
const int M = 1e4+7;

ll res[N][N];
stack<pii> st;
vector<pii> adj[M];
ll dist[M], seen[M];
int n, m, s;
int t;
ll st[N][2];
int x, y;
int p[N];
int ts;

int djs (int u) {
    priority_queue<pii> pq;

    for (int i = 0; i < n; i++) {
        dist[i] = 1e12;
        seen[i] = 0;
    }
    dist[u] = 0;

    pq.push(pii(0, u));

    while (!pq.empty()) {
        int cur = pq.top().second;
        int dst = -pq.top().first;
        pq.pop();

        if (seen[cur] == 1) continue;
        seen[cur] = 1;
        
        for (pii ed : adj[cur]) {
            int v = ed.first;
            int nxt = dst + ed.second;
            if (!seen[v] && (dist[v] == -1 || dist[v] > nxt)) {
                dist[v] = nxt;
                pq.push(pii(-dist[v], v));
            }
        }
    }
}

int main () {
    scanf("%d", &ts);
    while (ts--) {
        scanf("%d %d %d %d", &n, &m, &s, &t);

        for (int i = 0; i < n; i++)
            adj[i].clear();

        for (int i = 0; i < m; i++) {
            int a, b, w;
            scanf("%d %d %d", &a, &b, &w);
            a--; b--;

            adj[a].push_back(pii(b, w));
            adj[b].push_back(pii(a, w));
        }
        
        for (int i = 0; i < s; i++) {
            scanf("%d %d", &st[i][0], &st[i][1]);
            st[i][0]--;
            p[i] = i;
        }
        scanf("%d %d", &x, &y);
        x--; y--;

        p[s] = s;
        st[s][0] = y;
        st[s][1] = 0;

        for (int _i = 0; _i <= s; _i++) {
            int i = st[_i][0];
            ll w = st[_i][1];

            djs(i);

            for (int _j = 0; _j <= s; _j++) {
                int j = st[_j][0];
                res[i][j] = dist[j];
            }
        }

        for (int _i = 0; _i < s; _i++)
            for (int _j = 0; _j <= s; _j++)
                printf("%d %d : %lld\n", st[_i][0]+1, st[_j][0]+1, res[st[_i][0]][st[_j][0]]);

        sort(p, p+s, [] (int i, int j) {
            return st[i][1] < st[j][1];
        });

        for (int _k = s-1; _k >= 0; _k--) {
            int k = st[p[_k]][0];
            
            for (int _i = 0; _i < s; _i++) {
                int i = st[p[_i]][0];
                for (int _j = 0; _j <= s; _j++) {
                    int j = st[p[_j]][0];
                    res[i][j] = min(res[i][j], res[i][k] + res[k][j]);
                }
            }
        }

        printf("%lld\n", res[x][y]);
    }
}
