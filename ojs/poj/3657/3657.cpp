#include <iostream>
#include <algorithm>
//#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#define debug if(true)
#else
#define debug if(false)
#endif

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;

#define pb push_back

const int N = 5e6 + 7;

int n, q;
int v[N][3];
int p[N];

int vs[N], lm[N][2], tr;

void build (int u, int l, int r) {
    lm[u][0] = l;
    lm[u][1] = r;
    vs[u] = 0;

    if (l == r) return;
    int md = (l+r)/2;
    build(2*u, l, md);
    build(2*u+1, md+1, r);
}

bool use (int u, int l, int r) {
    if (l <= lm[u][0] && lm[u][1] <= r) {
        vs[u] = tr;
    } else if (!(vs[u] == tr || lm[u][1] < l || r < lm[u][0])) {
        bool o = use(2*u, l, r);
        if (use(2*u+1, l, r) && o)
            vs[u] = tr;
    }

    return (vs[u] == tr);
}

bool get (int u, int l, int r) {
    if (lm[u][1] < l || r < lm[u][0] || vs[u] == tr)
        return 1;
    if (l <= lm[u][0] && lm[u][1] <= r)
        return (vs[u] == tr);
    return (get(2*u,l,r) && get(2*u+1,l,r));
}

bool join (pii & a, pii b) {
    a.first = max(a.first, b.first);
    a.second = min(a.second, b.second);
    if (a.first > a.second)
        return 0;
    return 1;
}

bool ord (int i, int j) {
    return v[i][2] < v[j][2];
}

bool solve (int q) {
    tr++;

    for (int i = 0; i <= q; i++)
        p[i] = i;
    sort(p, p+q+1, ord);

    pii itv(1, n);
    int l = q;
    for (int i = q; i >= 0; i--) {
        if (!join(itv, pii(v[p[i]][0], v[p[i]][1])))
            return 0;
        if (!i || v[p[i]][2] != v[p[i-1]][2]) {
            if (get(1, itv.first, itv.second))
                return 0;
            itv.first = 1;
            itv.second = n;
            for (int j = i; j <= l; j++)
                use(1, v[p[j]][0], v[p[j]][1]);
            l = i-1;
        }
    }

    return 1;
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> q;

    build(1, 1, n);

    for (int i = 0; i < q; i++) {
        cin >> v[i][0] >> v[i][1] >> v[i][2];
    }

    
    int lo = 0;
    int hi = q;

    while (lo < hi) {
        int md = (lo+hi)/2;
        if (solve(md))
            lo = md+1;
        else
            hi = md;
    }
    
    cout << (lo+1)%(q+1) << endl;
}
