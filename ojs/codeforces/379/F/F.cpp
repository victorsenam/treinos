#include <bits/stdc++.h>
#define debug if (1)

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 2e6+7;

int n, qs;
int adt[N], sz[N];
vector<int> adj[N];
ll rs[N];

int getsz (int u, int p) {
    sz[u] = 1;
    for (int v : adj[u]) {
        if (v == p || sz[v] == -1) continue;
        sz[u] += getsz(v, u);
    }
    return sz[u];
}

struct onp {
    int u, p, t, d, o;

    bool operator < (const onp & ot) const {
        return t < ot.t;
    }
} mx[2];
queue<onp> qu;
onp vt[N];

bool beats (onp & a, onp & b) {
    return a.d > b.d;
}

void cent (int u) {
    int siz = getsz(u, u);
    int w = u;
    do {
        u = w;
        for (int v : adj[u]) {
            if (sz[v] == -1 || sz[v] >= sz[u] || sz[v] + sz[v] < siz)
                continue;
            w = v;
            break;
        }
    } while (w != u);
    
    sz[u] = -1;

    qu.push(onp({u,u,adt[u],0,u}));
    int vs = 0;

    while (!qu.empty()) {
        onp cur = qu.front();
        qu.pop();

        vt[vs++] = cur;

        for (int v : adj[cur.u]) {
            if (v == cur.p || sz[v] == -1)
                continue;
            onp nx = onp({v,cur.u,max(cur.t,adt[v]),cur.d+1,cur.o});
            if (cur.o == u)
                nx.o = v;
            qu.push(nx);
        }
    }

    mx[0] = mx[1] = onp({n,n,0,-N,n});

    sort(vt,vt+vs);
    for (int i = 0; i < vs; i++) {
        onp & cur = vt[i];

        ll vl = mx[0].d;
        if (mx[1].o != cur.o)
            vl = mx[1].d;
        rs[cur.t] = max(rs[cur.t], vl + cur.d);

        if (cur.d > mx[1].d) {
            if (cur.o != mx[1].o)
                mx[0] = mx[1];
            mx[1] = cur;
        } else if (cur.d > mx[0].d && mx[1].o != cur.o) {
            mx[0] = cur;
        }
    }

    for (int v : adj[u]) {
        if (sz[v] == -1) continue;
        cent(v);
    }
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> qs;

    n = 4;
    adj[0].reserve(3);
    for (int i = 1; i < n; i++) {
        adj[i].reserve(3);
        adj[0].pb(i);
        adj[i].pb(0);
    }

    for (int i = 1; i <= qs; i++) {
        int v;
        cin >> v;
        v--;

        for (int k = 0; k < 2; k++) {
            adj[n].reserve(3);
            adt[n] = i;
            adj[n].pb(v);
            adj[v].pb(n);
            n++;
        }
    }

    cent(0);

    ll mx = 2;
    for (int i = 1; i <= qs; i++) {
        mx = max(mx, rs[i]);
        cout << mx << " ";
    }
    cout << endl;
}
