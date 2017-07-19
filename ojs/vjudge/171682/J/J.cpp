#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back
#define y1 alsidalijd
#define y2 aasdasf

struct ev {
    int x, i;
    bool add;
    bool operator < (ev o) const { return x < o.x; }
};

const int N = 112345;

int val[N << 2];
int lz[N << 4]; bool llz[N << 4];
void unlaze(int i, int l, int r) {
    if(!llz[i]) return;
    if(l == r) {
        val[l] = lz[i];
    } else {
        lz[2 * i] = lz[2 * i + 1] = lz[i];
        llz[2 * i] = llz[2 * i + 1] = true;
    }
    llz[i] = false;
}

void set_(int i, int l, int r, int ql, int qr, int x) {
    unlaze(i, l, r);
    if(l > qr || r < ql) return;
    if(l >= ql && r <= qr) {
        lz[i] = x;
        llz[i] = true;
        unlaze(i, l, r);
        return;
    }
    int m = (l + r) / 2;
    set_(2 * i, l, m, ql, qr, x);
    set_(2 * i + 1, m + 1, r, ql, qr, x);
}

int get(int i, int l, int r, int p) {
    unlaze(i, l, r);
    if(l == r) return val[l];
    int m = (l + r) / 2;
    if(p <= m) return get(2 * i, l, m, p);
    else return get(2 * i + 1, m + 1, r, p);
}

int p[N];
int x1[N], x2[N], y1[N], y2[N];

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int i, n;
    cin >> n;
    vector<int> all;
    for(i = 0; i < n; i++) {
        cin >> x1[i] >> y1[i] >> x2[i] >> y2[i];
        all.pb(x1[i]);
        all.pb(x2[i]);
        all.pb(y1[i]);
        all.pb(y2[i]);
    }
    sort(all.begin(), all.end());
    all.erase(unique(all.begin(), all.end()), all.end());
    vector<ev> evs;
    for(i = 0; i < n; i++) {
        x1[i] = lower_bound(all.begin(), all.end(), x1[i]) - all.begin();
        x2[i] = lower_bound(all.begin(), all.end(), x2[i]) - all.begin();
        y1[i] = lower_bound(all.begin(), all.end(), y1[i]) - all.begin();
        y2[i] = lower_bound(all.begin(), all.end(), y2[i]) - all.begin();
        evs.pb(ev{x1[i], i, true});
        evs.pb(ev{x2[i], i, false});
    }
    int sn = all.size();
    for(i = 0; i < sn; i++)
        val[i] = -1;
    sort(evs.begin(), evs.end());
    for(ev e : evs) {
        if(e.add) {
            p[e.i] = get(1, 0, sn - 1, y1[e.i]);
            set_(1, 0, sn - 1, y1[e.i], y2[e.i], e.i);
        } else {
            set_(1, 0, sn - 1, y1[e.i], y2[e.i], p[e.i]);
        }
    }
    for(i = 0; i < n; i++)
        cout << p[i] << '\n';
}
