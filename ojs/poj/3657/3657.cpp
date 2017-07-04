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

const int N = 1e6 + 7;

int n, q;
int v[N][3];
int p[N];

int sg[N], lz[N], ch[N][2], lm[N][2], qs;

void create (int & u, int l, int r) {
    if (u != -1) return;
    u = qs++;
    ch[u][0] = ch[u][1] = -1;
    lz[u] = sg[u] = 0;
    lm[u][0] = l; lm[u][1] = r;
}

void refresh (int u) {
    if (lm[u][0] == lm[u][1]) {
        if (lz[u]) { 
            sg[u] = 1;
            lz[u] = 0;
        }
        return;
    }

    create(ch[u][0], lm[u][0], (lm[u][0]+lm[u][1])/2);
    create(ch[u][1], (lm[u][0]+lm[u][1])/2+1, lm[u][1]);

    if (lz[u]) {
        lz[u] = 0;
        sg[u] = (lm[u][1] - lm[u][0] + 1);
        lz[ch[u][0]] = lz[ch[u][1]] = 1;
    }
}

int st (int & u, int l, int r) {
    refresh(u);
    if (lm[u][1] < l || r < lm[u][0]) return sg[u];
    if (l <= lm[u][0] && lm[u][1] <= r) {
        lz[u] = 1;
        refresh(u);
        return sg[u];
    }
    refresh(u);
    return sg[u] = st(ch[u][0], l, r) + st(ch[u][1], l, r);
}

int get (int & u, int l, int r) {
    if (lm[u][1] < l || r < lm[u][0]) return 0;
    refresh(u);
    if (l <= lm[u][0] && lm[u][1] <= r) return sg[u];
    return get(ch[u][0], l, r) + get(ch[u][1], l, r);
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
    qs = 1;
    sg[0] = lz[0] = 0;
    lm[0][0] = 1; lm[0][1] = n;
    ch[0][0] = ch[0][1] = -1;
    int root = 0;

    for (int i = 0; i <= q; i++)
        p[i] = i;
    sort(p, p+q+1, ord);

    pii itv(1, n);
    int l = q;
    for (int i = q; i >= 0; i--) {
        if (!join(itv, pii(v[p[i]][0], v[p[i]][1])))
            return 0;
        if (!i || v[p[i]][2] != v[p[i-1]][2]) {
            if (get(root, itv.first, itv.second) == itv.second - itv.first + 1)
                return 0;
            itv.first = 1;
            itv.second = n;
            for (int j = i; j <= l; j++)
                st(root, v[p[j]][0], v[p[j]][1]);
            l = i-1;
        }
    }

    return 1;
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> q;

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
