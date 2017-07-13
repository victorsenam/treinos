#include <bits/stdc++.h>
#define debug if (1)

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e3+7;

ll n, k;
ll a[N];
set<ll> s;

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        s.insert(-a[i]);
        for (ll j = 2; j*j <= a[i]; j++)
            if (a[i]%j == 0) {
                s.insert(-j);
                s.insert(-(a[i]/j));
            }
    }

    for (ll y : s) {
        ll x = -y;
        ll loc = 0;
        for (int i = 0; i < n; i++) {
            loc += (x - (a[i]%x))%x;
            cout << "--" << a[i]%x << endl;
        }
        if (loc <= k) {
            cout << x << endl;
            return 0;
        }

    }
    cout << 1 << endl;
}
