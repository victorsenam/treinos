#include <bits/stdc++.h>

using namespace std;

const int MAXV = 210, INF = 0x7FFFFFFF;

struct edge {
    int dest, rev, cap, f;
    edge(int dest, int rev, int cap) : dest(dest), rev(rev), cap(cap) {
        f = 0;
    }
};

int dist[MAXV + 1], ptr[MAXV + 1];
vector<edge> adj[MAXV + 1];
int V, S, T;

void add_edge(int a, int b, int cap = 1) {
    adj[a].push_back(edge(b, adj[b].size(), cap));
    adj[b].push_back(edge(a, adj[a].size() - 1, 0));
}

bool bfs() {
    for(int i = 1; i <= V; i++)
        dist[i] = -1;
    dist[S] = 0;
    queue<int> q;
    q.push(S);
    while(!q.empty()) {
        int v = q.front();
        q.pop();
        for(int i = 0; i < adj[v].size(); i++) {
            edge e = adj[v][i];
            if(dist[e.dest] == -1 && e.cap > e.f) {
                dist[e.dest] = dist[v] + 1;
                q.push(e.dest);
            }
        }
    }
    return dist[T] != -1;
}

int dfs(int v, int f) {
    if(v == T) return f;
    for(; ptr[v] < adj[v].size(); ++ptr[v]) {
        edge &e = adj[v][ptr[v]];
        if(dist[e.dest] == dist[v] + 1 && e.cap > e.f) {
            int df = dfs(e.dest, min(f, e.cap - e.f));
            if(df > 0) {
                e.f += df;
                adj[e.dest][e.rev].f -= df;
                return df;
            }
        }
    }
    return 0;
}

int max_flow() {
    int flow = 0;
    while(bfs()) {
        for(int i = 1; i <= V; i++)
            ptr[i] = 0;
        while(true) {
            int df = dfs(S, INF);
            if(df == 0) break;
            flow += df;
        }
    }
    return flow;
}

void clear() {
    for(int i = 1; i <= V; i++)
        adj[i].clear();
}

const int MAX = MAXV;

int m[MAX][MAX], vis[MAX], n;

bool ok(int v, int u) {
    if(v == u) return true;
    vis[v] = 1;
    for(int i = 0; i < n; i++) {
        if(m[v][i] && !vis[i]) {
            if(ok(i, u)) return true;
        }
    }
    return false;
}

void dfs2(int v) {
    vis[v] = 1;
    for(edge &e : adj[v]) {
        int u = e.dest;
        if(e.cap - e.f != 0 && !vis[u]) {
            dfs2(u);
        }
    }
}

int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            scanf("%d", &m[i][j]);
    V = T = 2*n + 2;
    S = 2*n + 1;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(i == j) continue;
            for(int k = 0; k < n; k++) vis[k] = 0;
            if(ok(i, j)) {
                add_edge(i + 1, j + n + 1);
            }
        }
    }
    for(int i = 0; i < n; i++) {
        add_edge(S, i + 1);
        add_edge(i + n + 1, T);
    }
    printf("%d\n", n - max_flow());
    for(int i = 1; i <= 2*n; i++) vis[i] = mrk[i] = 0;
    dfs2(S);
    bool first = true;
    for(int i = 1; i <= n; i++) {
        if(vis[i] && !vis[i + n]) {
            if(first) first = false;
            else printf(" ");
            printf("%d", i);
        }
    }
    printf("\n");
    return 0;
}
