#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;

const int N = 5e4+7;

ll n, v;
ll t;
ll x[2][N], y[2][N];
int p[2][N], q[2][N];

ll vl[N<<2];
int lm[N<<2][2];

void build (int u, int l, int r) {
    lm[u][0] = l; lm[u][1] = r;
    vl[u] = 0;
    if (l == r)
        return;
    int md = (l+r)/2;
    build(2*u, l, md);
    build(2*u+1, md+1, r);
}

ll get (int u, int l, int r) {
    if (lm[u][1] < l || r < lm[u][0])
        return 0;
    if (l <= lm[u][0] && lm[u][1] <= r)
        return vl[u];
    return max(get(2*u,l,r), get(2*u+1,l,r));
}

ll upd (int u, int i, ll x) {
    if (lm[u][1] < i || i < lm[u][0])
        return vl[u];
    if (lm[u][0] == lm[u][1] && lm[u][0] == i)
        return (vl[u] = x);
    return vl[u] = max(upd(2*u,i,x),upd(2*u+1,i,x));
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> t;
    while (t--) {
        cin >> n >> v;

        for (int k = 0; k < 2; k++) {
            for (int i = 0; i < n; i++) {
                ll a, b, c, d;
                cin >> a >> b >> c >> d;
                x[k][i] = min(a,c);
                y[k][i] = abs(d-b);
                p[k][i] = i;
            }
            sort(p[k], p[k]+n, [k] (int i, int j) {
                return x[k][i] < x[k][j];
            });
            for (int i = 0; i < n; i++)
                q[k][p[k][i]] = i;
        }

        bool ok = 1;
        build(1, 0, n-1);
        for (int _i = 0; ok && _i < n; _i++) {
            int i = p[0][_i];
            int _j = q[1][i];

            ll mm = get(1, _j, n-1);
            if (mm + y[0][i] > v) {
                ok = 0;
            } else {
                upd(1, _j, y[0][i]);
            }
        }

        if (ok)
            cout << "ANO" << endl;
        else
            cout << "NIE" << endl;
    }
}
