#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;

const int N = 1e6+7;
ll tr[N << 2], lz[N << 2];
inline void unlaze(int i, int l, int r) {
    tr[i] += lz[i];
    if(l != r) {
        lz[2 * i] += lz[i];
        lz[2 * i + 1] += lz[i];
    }
    lz[i] = 0;
}

void add(int i, int l, int r, int ql, int qr, ll x) {
    unlaze(i, l, r);
    if(l > qr || r < ql) return;
    if(l >= ql && r <= qr) {
        lz[i] = x;
        unlaze(i, l, r);
        return;
    }
    int m = (l + r) / 2;
    add(2 * i, l, m, ql, qr, x);
    add(2 * i + 1, m + 1, r, ql, qr, x);
    tr[i] = max(tr[2 * i], tr[2 * i + 1]);
}

ll get(int i, int l, int r, int ql, int qr) {
    unlaze(i, l, r);
    if(l > qr || r < ql) return 0;
    if(l >= ql && r <= qr) return tr[i];
    int m = (l + r) / 2;
    return max(get(2 * i, l, m, ql, qr), get(2 * i + 1, m + 1, r, ql, qr));
}

int oc[N][2];
int v[N], val[N];
int main () {
    int f, p, i;
    scanf("%d %d", &p, &f);
    for(i = 0; i < p; i++)
        scanf("%d", &v[i]), v[i]--;
    for(i = 0; i < f; i++) {
        scanf("%d", &val[i]);
        oc[i][0] = oc[i][1] = p;
    }
    ll best = 0;
    for(i = p - 1; i >= 0; i--) {
        int r = p;
        r = oc[v[i]][0];
        if (i < r)
            add(1, 0, p - 1, i, r-1, val[v[i]]);
        int l = r;
        r = oc[v[i]][1];
        if (l < r)
            add(1, 0, p - 1, l, r-1, -val[v[i]]);
        best = max(best, get(1, 0, p - 1, i, p - 1));

        oc[v[i]][1] = oc[v[i]][0];
        oc[v[i]][0] = i;
    }
    printf("%lld\n", best);
}
