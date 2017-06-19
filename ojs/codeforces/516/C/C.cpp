#include <bits/stdc++.h>
//#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define debug(...) {}
#endif

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e6;

int n, m;
ll d[N], h[N];
ll q[N][2];
int p[N];

struct info {
    ll sum, bes;
    ll lef, rig;

    ll l, r;
} vl[N];

info join (info a, info b) {
    info nw;
    nw.l = a.l; nw.r = b.r;

    b.lef = max(b.lef, h[b.l] + h[b.l]);
    a.rig = max(a.rig, h[a.r] + h[a.r]);

    nw.sum = a.sum + d[a.r] + b.sum;
    nw.lef = max({a.lef, a.sum + d[a.r] + b.lef});
    nw.rig = max({b.rig, b.sum + d[a.r] + a.rig});
    nw.bes = max({a.bes, b.bes, nw.lef + h[a.l] + h[a.l], nw.rig + h[b.r] + h[b.r], a.rig + b.lef + d[a.r]});
    return nw;
}

info build (int i, int l, int r) {
    if (l == r) {
        vl[i].l = l; vl[i].r = r;
        vl[i].sum = 0;
        vl[i].lef = vl[i].rig = vl[i].bes = -1e10;
        return vl[i];
    }
    int md = (l+r)/2;
    vl[i] = join(build(2*i, l, md), build(2*i+1, md+1, r));
    return vl[i];
}

info get (int i, int l, int r) {
    //printf("[%d,%d] : %d[%lld,%lld]\n", l, r, i, vl[i].l, vl[r].r);
    if (l <= vl[i].l && vl[i].r <= r)
        return vl[i];
    if (l > vl[i].r || r < vl[i].l) {
        info nw;
        nw.l = nw.r = N-1;
        nw.sum = 0;
        nw.bes = nw.lef = nw.rig = -1e10;
        return nw;
    }

    return join(get(2*i, l, r), get(2*i+1, l, r));
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        cin >> d[i];
        d[i+n] = d[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> h[i];
        h[i+n] = h[i];
    }
    h[N-1] = -1e10;

    build(1, 0, 2*n-1);

    for (int i = 0; i < m; i++) {
        cin >> q[i][0] >> q[i][1];
        q[i][0]--; q[i][1]--;

        ll rs = 0;
        if (q[i][1] < q[i][0]) {
            rs = get(1, q[i][1]+1, q[i][0]-1).bes;
        } else {
            rs = get(1, q[i][1]+1, q[i][0]+n-1).bes;
        }

        cout << rs << endl;
    }
}
