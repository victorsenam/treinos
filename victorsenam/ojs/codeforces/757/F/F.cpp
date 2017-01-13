#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;

const int N = 2e5+7;
const int M = 6e5+7;

int n, m, o;
int to[M], es;
ll wg[M], dist[N];
int visi[N], from[N], dg[N];
vector<int> adj[N];
int p[N];

int t[N];
set<int> s[N][2];

struct node {
    int u, fr;
    ll d;

    bool operator < (const node & ot) const {
        if (ot.d != d) return d > ot.d;
        return u < ot.u;
    }
};

bool isbad (int ed)
{ return (visi[to[ed]] && visi[to[ed^1]] && dist[to[ed^1]] + wg[ed] == dist[to[ed]]); }

void rem (int ed, int u) {
    if (!isbad(ed)) return;
    if (s[u][0].find(ed) != s[u][0].end()) {
        s[u][0].erase(ed);
    } else {
        s[u][1].insert(ed);
    }
}

void add (int ed, int u) {
    if (!isbad(ed)) return;
    if (s[u][1].find(ed) != s[u][1].end()) {
        s[u][1].erase(ed);
    } else {
        s[u][0].insert(ed);
    }
}

int main () {
    scanf("%d %d %d", &n, &m, &o);
    o--;

    es = 2;
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d %lld", &a, &b, &wg[es]);
        wg[es+1] = wg[es]; a--; b--;

        to[es] = b; adj[a].push_back(es++);
        to[es] = a; adj[b].push_back(es++);
    }

    priority_queue<node> pq;
    node att;
    att.u = o;
    att.d = 0;
    att.fr = 0;
    dist[att.u] = att.d;
    visi[att.u] = 1;
    pq.push(att);

    while (!pq.empty()) {
        att = pq.top();
        pq.pop();

        if (visi[att.u] == 2) continue;
        visi[att.u] = 2;
        from[att.u] = att.fr;
        if (att.fr) {
            if (att.fr < 0 || to[att.fr] < 0 || to[att.fr] >= N)
                while(true);
            dg[to[att.fr]]++;
        }

        for (int ed : adj[att.u]) {
            node nxt = att;
            nxt.u = to[ed];
            nxt.fr = ed^1;
            nxt.d += wg[ed];

            if (!visi[nxt.u] || nxt.d < dist[nxt.u]) {
                visi[nxt.u] = 1;
                dist[nxt.u] = nxt.d;
                pq.push(nxt);
            }
        }
    }

    queue<int> qu;
    for (int i = 0; i < n; i++) {
        if (visi[i] == 1)
            while(true);
        if (visi[i] && dg[i] == 0)
            qu.push(i);
        p[i] = i;
    }

    int res = 0;
    while (!qu.empty()) {
        int u = qu.front();
        qu.pop();

        if (u == o) break;

        t[u]++;       
        for (int ed : adj[u])
            rem(ed, p[u]);

        if (s[p[u]][0].empty())
            res = max(res, t[u]);

        for (int ed : adj[u])
            add(ed^1, p[u]);

        if (from[u] < 2)
            while(true);
        int v = to[from[u]];
        if (s[p[u]][0].size() + s[p[u]][1].size() > s[p[v]][0].size() + s[p[v]][1].size()) {
            swap(p[u], p[v]);
        }
        t[v] += t[u];
        for (int ed : s[p[u]][0])
            add(p[v], ed);
        s[p[u]][0].clear();
        for (int ed : s[p[u]][1])
            rem(p[v], ed);
        s[p[u]][1].clear();

        dg[v]--;
        if (!dg[v])
            qu.push(v);
    }

    printf("%d\n", res);
}
