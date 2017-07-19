#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back
#define pos first
#define qtd second

const ll MOD = 1e9+7;
const int N = 1e6+7;

int ts;
int n;
set<pii> s;
bool isimp;
ll p2[N];
ll v[N];

inline ll mod (ll x)
{ return ((x%MOD) + MOD)%MOD; }

inline ll pequenos (ll i, ll x) {
    if (x <= n/2)
        return x;
    else
        return i - 1 - n + x;
}

ll func (ll l, ll r) {
    return mod(p2[n-l] - p2[n-1-r]);
}

ll valor (pii l, pii r, int ty) {
    if (r.pos == n+1) { // intervalo até o fim
        if (!ty)
            return 0;
        else
            return func(l.pos+1, n-1);
    } else {
        ll k = r.qtd - l.qtd - (v[r.pos] <= n/2);        
        ll m = r.pos - l.pos - 1;
        ll L,R;
        if (k < 0 || k > m) {
            return isimp = 1;
        }
        if (!ty) {
            L = l.pos + 1 + k;
            R = r.pos - 1;
        } else {
            L = l.pos + 1;
            R = l.pos + m - k;
        }
        return func(L,R);
    }
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    p2[0] = 1;
    for (int i = 1; i < N; i++)
        p2[i] = mod(p2[i-1] + p2[i-1]);

    cin >> ts;

    while (ts--) {
        ll res[2] = {0,0};
        cin >> n;
        isimp = 0;

        s.clear();
        s.insert(pii(0,0));
        s.insert(pii(n+1,n+1));
        res[1] = func(1, n - 1);
        res[0] = 0;

        for (int i = 0; i < n/2; i++) {
            pii a;
            int vl;
            cin >> a.pos >> vl;
            a.qtd = pequenos(a.pos, vl);
            v[a.pos] = vl;

            if (vl > n/2) {
                res[0] = mod(res[0] + func(a.pos, a.pos));
                res[1] = mod(res[1] + func(a.pos, a.pos));
            }

            auto r = s.lower_bound(a);
            auto l = r;
            l--;

            for (int k = 0; k < 2; k++) {
                res[k] = mod(res[k] - valor(*l, *r, k));
                res[k] = mod(res[k] + valor(a, *r, k));
                res[k] = mod(res[k] + valor(*l, a, k));
            }
            s.insert(a);
            if (isimp)
                cout << -1 << endl;
            else
                cout << res[0] << " " << res[1] << endl;
        }
    }

}
