#include <bits/stdc++.h>
#define debug if (1)

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e5+7;

int n;
double s;
double x[N], v[N];
int d[N];

double go (ll in, bool db=0) {
    double t[2] = {1./0., 1./0.};

    for (int i = 0; i < n; i++) {
        ll p = in;
        ll x = ::x[i];
        ll v = ::v[i];

        if (d[i] == 1) {
            x = 1e6 - x;
            p = 1e6 - p;
        }

        double fc;

        if (p > x)
            fc = (p - x)/(s - v);
        else
            fc = 1./0.;

        double fn = double(x)/v;
        double rs = fn;

        if (fn > fc)
            rs = fc + (x - fc*v)/(v + s);

        if (db)
            cout << i << ": fn:" << fn << " fc:" << fc << " rs:" << rs << endl;
        
        t[d[i]] = min(t[d[i]], rs);
    }
    if (db)
        cout << "=================" << endl;

    return max(t[0], t[1]);
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> s;
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> v[i] >> d[i];
        d[i]--;
    }

    ll lo = 0, hi = 1e6;

    while (hi - lo > 5) {
        ll q1 = (lo + lo + hi)/3;
        ll q2 = (lo + hi + hi)/3;

        if (go(q1) < go(q2))
            hi = q2;
        else
            lo = q1;
    }

    double res = 1./0.;
    for (ll i = lo; i <= hi; i++){
        res = min(res, go(i, 0));
    }

    cout << setprecision(20) << res << endl;
}
