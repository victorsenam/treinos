#include <bits/stdc++.h>
#define debug if (1)

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

ll k, n, q, r;

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> k;

    if (k >= 50) {
        n = 50;

        q = k/n - 1;
        r = k%n;

        cout << n << endl;
        for (int i = 0; i < n; i++) {
            ll x;
            if (i < r) {
                x = n + q + 1;
            } else {
                x = n + q - r;
            }
            cout << x << " ";
        }
        cout << endl;
    } else if (k >= 2) {
        cout << k << endl;
        for (int i = 0; i < k; i++)
            cout << k << " ";
        cout << endl;
    } else if (k == 1) {
        cout << "2\n2 0" << endl;
    } else {
        cout << "2\n0 0" << endl;
    }
}
