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

const int N = 1e5+7;
const ll MOD = 1e9+7;

ll memo[N][2];

ll mod (ll x) {
    return x %MOD;
}

int ts;
int n;

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> ts;
    while (ts--) {
        cin >> n;

        ll t, st, p, q;

        cin >> t;
        st = 0;
        p = t;
        q = 1;

        //cout << "T Q P ST" << endl;

        //cout << t << " " << q << " " << p << " " << st << endl;

        for (int i = 1; i < n; i++) {
            ll v;
            cin >> v;

            ll nq = mod(q*2ll);
            ll nt = mod(t + q*v + st + p*v);
            ll np = mod(p*v + v*q);
            ll nst = mod(st + t);

            t = nt;
            q = nq;
            p = np;
            st = nst;

            //cout << t << " " << q << " " << p << " " << st << endl;
        }

        cout << t << endl;
    }
}
