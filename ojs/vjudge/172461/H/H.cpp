#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back
#define den first
#define itt second

const int N = 50;
const int M = (1<<21);

struct trip { 
    ll den, itt, msk;

    bool operator < (trip o) const {
        if (den != o.den) return den < o.den;
        return itt > o.itt;
    }
};

int n;
ll b;
trip v[N];

trip lf[M];
int lfs;

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> b;
    for (int i = 0; i < n; i++) {
        cin >> v[i].den >> v[i].itt;
        v[i].msk = i;
    }

    if (n == 1) {
        if (v[0].den == 1 && b == 1) {
            cout << "1\n" << 1 << endl;
        } else {
            cout << "-1" << endl;
        }
        return 0;
    }

    sort(v, v+n);

    for (ll msk = 0; msk < (1<<(n/2)); msk++) {
        pii acc;
        acc.den = 0;
        acc.itt = 0;
        bool ok = 1;

        for (int j = 0; ok && j < n/2; j++) {
            if (msk&(1ll<<j)) {
                if (v[j].den > acc.den + 1) ok = 0;
                acc.den += v[j].den;
                acc.itt += v[j].itt;
            }
        }
        
        if (ok) {
            lf[lfs].den = acc.den;
            lf[lfs].itt = acc.itt;
            lf[lfs].msk = msk;
            lfs++;
        }
    }

    sort(lf, lf+lfs);

    int cr = 0;
    for (int i = 0; i < lfs; i++) {
        while (cr && lf[i].itt <= lf[cr-1].itt)
            cr--;
        lf[cr] = lf[i];
        cr++;
    }
    lfs = cr;

    ll opt = 0;
    ll itt = LLONG_MAX;
    for (ll msk = 0; msk < (1ll<<((n+1)/2)); msk++) {
        pii acc;
        acc.den = 0;
        acc.itt = 0;

        ll restr = 0;

        for (int j = n/2; j < n; j++) {
            if (msk&(1ll<<(j-(n/2)))) {
                restr = max(restr, v[j].den - acc.den - 1);
                acc.den += v[j].den;
                acc.itt += v[j].itt;
            }
        }

        restr = max(restr, b - acc.den);

        int pp = lower_bound(lf, lf+lfs, trip({restr, LLONG_MAX, 0})) - lf;
        if (pp == lfs)
            continue;

        acc.den += lf[pp].den;
        acc.itt += lf[pp].itt;
        if (itt > acc.itt) {
            opt = (lf[pp].msk|(msk<<(n/2)));
            itt = acc.itt;
        }
    }


    if (opt == 0) {
        cout << -1 << endl;
        return 0;
    }

    cout << __builtin_popcountll(opt) << endl;
    for (int i = 0; i < n; i++) {
        if (opt&(1ll<<i))
            cout << v[i].msk+1 << " ";
    }
    cout << endl;
}
