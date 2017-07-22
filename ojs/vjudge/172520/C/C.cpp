#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 312345;
const int M = N * 25; ///asdasdasdasd

int L[M], R[M], tr[M];

int en = 1;
int build(int l, int r) {
    int i = en++;
    if(l != r) {
        int m = (l + r) / 2;
        L[i] = build(l, m);
        R[i] = build(m + 1, r);
    }
    return i;
}

inline int cp(int i) {
    int u = en++;
    L[u] = L[i];
    R[u] = R[i];
    tr[u] = tr[i];
    return u;
}

int set_(int oi, int l, int r, int p, int x) {
    int i = cp(oi);
    if(l == r) {
        tr[i] = x;
        return i;
    }
    int m = (l + r) / 2;
    if(p <= m) L[i] = set_(L[i], l, m, p, x);
    else R[i] = set_(R[i], m + 1, r, p, x);
    return i;
}

int get(int i, int l, int r, int p) {
    if(l == r) return tr[i];
    int m = (l + r) / 2;
    if(p <= m) return get(L[i], l, m, p);
    else return get(R[i], m + 1, r, p);
}

int k[N], p[N], sn;
vector<int> kv[N], vv[N];
int seg[N];

#define printf(args...) ((void) 0)

vector<int> adj[N];
void dfs(int u, int rt) {
    seg[u] = rt;
    for(int i = 0; i < k[u]; i++) {
        printf("%d sets %d as %d\n", u, kv[u][i], vv[u][i]);
        seg[u] = set_(seg[u], 0, sn - 1, kv[u][i], vv[u][i]);
    }
    for(int v : adj[u])
        dfs(v, seg[u]);
}

map<string, int> vs, ks;
string inv[N];

int main () {
    ios::sync_with_stdio(0);
    string s;
    int i, n, q, j, g;
    cin >> n;
    vs["N/A"] = 0; inv[0] = "N/A";
    for(i = 0; i < n; i++) {
        cin >> p[i] >> k[i]; p[i]--;
        if(i) adj[p[i]].pb(i);
        for(j = 0; j < k[i]; j++) {
            cin >> s;
            printf(":%s\n", s.c_str());
            for(g = 0; s[g] != '='; g++);
            string key = s.substr(0, g), val = s.substr(g + 1, s.size() - g - 1);
            if(!ks.count(key)) { ks[key] = ks.size() - 1; printf("[%s] = %d\n", key.c_str(), ks[key]); }
            if(!vs.count(val)) { vs[val] = vs.size() - 1; inv[vs[val]] = val; }
            kv[i].pb(ks[key]);
            vv[i].pb(vs[val]);
        }
    }
    sn = ks.size();
    dfs(0, build(0, sn - 1));
    cin >> q;
    for(i = 0; i < q; i++) {
        int a;
        cin >> a >> s; a--;
        printf("query %d %s\n", a, s.c_str());
        if(!ks.count(s)) { cout << "N/A\n"; cout.flush(); continue; }
        g = ks[s];
        printf("id %d\n", g);
        cout << inv[get(seg[a], 0, sn - 1, g)] << '\n';
        cout.flush();
    }
}
