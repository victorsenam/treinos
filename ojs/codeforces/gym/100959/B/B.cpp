#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back
#define x first
#define y second

vector<int> far(vector<pii> &p) {
    int l[4] = {0, 0, 0, 0};
    for(int i = 1; i < p.size(); i++) {
        if(p[i].x + p[i].y > p[l[0]].x + p[l[0]].y)
            l[0] = i;
        if(p[i].x - p[i].y > p[l[1]].x - p[l[1]].y)
            l[1] = i;
        if(-p[i].x + p[i].y > -p[l[2]].x + p[l[2]].y)
            l[2] = i;
        if(-p[i].x - p[i].y > -p[l[3]].x - p[l[3]].y)
            l[3] = i;
    }
    return vector<int>(l, l + 4);
}

vector<pii> p;

const int N = 112345;
int S[N], sz[N];
int find(int i) {
    if(S[S[i]] != S[i]) S[i] = find(S[i]);
    return S[i];
}

inline void join(int a, int b) {
    if((a = find(a)) == (b = find(b))) return;
    if(sz[a] < sz[b]) swap(a, b);
    sz[a] += sz[b];
    S[b] = a;
}

int main () {
    int i, j, n;
    scanf("%d", &n);
    ll D = 1e10;
    p.resize(n);
    for(i = 0; i < n; i++) S[i] = i, sz[i] = 1;
    for(i = 0; i < n; i++) scanf("%d %d", &p[i].x, &p[i].y);
    vector<int> l = far(p);
    for(i = 0; i < n; i++) {
        ll mx = -1; int id;
        for(j = 0; j < 4; j++) {
            ll dis = abs(p[i].x - p[l[j]].x) + abs(p[i].y - p[l[j]].y);
            if(dis > mx) {
                mx = dis;
                id = l[j];
            }
        }
        D = min(D, mx);
        join(i, id);
    }
    if(sz[find(0)] == n) { printf("%lld\n", D); return 0; }
    vector<pii> f[2];
    for(i = 0; i < n; i++)
        f[find(i) == find(0)].pb(p[i]);
    l = far(f[0]);
    ll mx = -1;
    for(pii x : f[1])
        for(j = 0; j < 4; j++)
            mx = max<ll>(mx, abs(x.x - f[0][l[j]].x) + abs(x.y - f[0][l[j]].y));
    D = min(D, mx);
    printf("%lld\n", D);
}
