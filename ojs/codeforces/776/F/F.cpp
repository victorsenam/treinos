#include <bits/stdc++.h>
#define debug if (0)

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 2e5+7;

struct Node {
    set<int> vtx;
    vector<int> adj;
    int sz;
    int rs;

    bool operator < (const Node & ot) const {
        auto it = vtx.rbegin();
        auto jt = ot.vtx.rbegin();

        while (it != vtx.rend() && jt != ot.vtx.rend()) {
            if (*it != *jt)
                return *it < *jt;
            ++it; ++jt;
        }
        return (it == vtx.rend());
    }
};

pii ed[N];
int n, m;
set<pii> avail;
map<pii, int> idx;
int ns;
Node nd[N];

int inner (pii x)
{ return x.second - x.first; }
int outer (pii x)
{ return n - x.second + x.first; }

int getsz (int u, int p) {
    nd[u].sz = 1;
    for (int v : nd[u].adj) {
        if (v == p || nd[v].sz == -1) continue;
        nd[u].sz += getsz(v, u);
    }
    return nd[u].sz;
}

void centroid (int u, int d) {
    int siz = getsz(u,u);

    int w = u;
    do {
        u = w;
        for (int v : nd[u].adj) {
            if (nd[v].sz == -1 || nd[v].sz >= nd[u].sz || nd[v].sz + nd[v].sz < siz)
                continue;
            w = v;
            break;
        }
    } while (u != w);

    nd[u].rs = d;
    nd[u].sz = -1;

    for (int v : nd[u].adj)
        if (nd[v].sz != -1)
            centroid(v, d+1);
}

void putin (pii aux, int x) {
    nd[x].vtx.insert(aux.first);
    nd[x].vtx.insert(aux.second);

    if ((aux.first + 1)%n != aux.second) {
        assert(idx.find(aux) != idx.end());
        nd[x].adj.pb(idx[aux]);
        nd[idx[aux]].adj.pb(x);
    }
}

void go (int l, int r, int x) {
    auto it = avail.lower_bound(pii(l,l));
    while (it != avail.end() && it->first < r) {
        putin(*it, x);
        auto jt = next(it);
        avail.erase(it);
        it = jt;
    }
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> ed[i].first >> ed[i].second;
        ed[i].first--; ed[i].second--;
        if (ed[i].first > ed[i].second)
            swap(ed[i].first, ed[i].second);
    }

    sort(ed, ed+m, [] (pii a, pii b) {
        return min(inner(a),outer(a)) < min(inner(b),outer(b));
    });

    pii extr(n-1,0);
    for (int i = 0; i < n-1; i++)
        avail.insert(pii(i,i+1));

    for (int i = 0; i < m; i++) {
        pii cur = ed[i];
        idx[cur] = i;
        if (inner(cur) <= outer(cur)) {
            go(cur.first, cur.second, i);
            avail.insert(cur);
        } else {
            go(cur.second, n-1, i);
            putin(extr,i);
            go(0, cur.first, i);
            extr = cur;
        }
    }

    go(0,n-1,m);
    putin(extr,m);

    centroid(0,0);

    sort(nd, nd+m+1);
    for (int i = 0; i <= m; i++) {
        cout << nd[i].rs + 1 << " ";
    }
    cout << endl;
}
