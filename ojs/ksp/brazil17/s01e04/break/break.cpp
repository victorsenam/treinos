#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;

int t;
ll a, b, c;

bool go (ll d, ll c) {
    if (c%d) return 0;
    if ((d <= a && c/d <= b) || (d <= b && c/d <= a)) {
        cout << 2 << endl;
        return 1;
    }
    return 0;
}

int main () {
    cin >> t;
    while (t--) {
        cin >> a >> b >> c;
        bool ok = 0;

        if (c == a*b)
            cout << 0 << endl;
        else if (c%b == 0 || c%a == 0)
            cout << 1 << endl;
        else {
            for (ll d = 1; !ok && d*d <= c; d++) {
                ok = go(d, c);
            }
            for (ll d = 1; !ok && d*d <= a*b-c; d++) {
                ok = go(d, a*b-c);
            }
            if (!ok)
                cout << 3 << endl;
        }
    }
}
