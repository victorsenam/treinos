#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;

const int N = 2e6+7;
const ll MOD = 1e9+7;

ll n;
ll v[N];

int main () {
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> v[i];

    sort(v, v+n);

    ll l = n;
    ll cur = 1;
    for (int i = n; i >= 1; i--) {
        while (l && v[l-1] >= i)
            l--;

        if (l >= i) {
            cout << 0 << endl;
            return 0;
        }
        cur = (cur * ll(n-l-ll(n-i)))%MOD;
    }
    cout << cur << endl;
}
