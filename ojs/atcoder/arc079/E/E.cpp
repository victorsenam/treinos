#include <bits/stdc++.h>
#define debug if (1)

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 60;

ll a[N], v[N];
ll n;

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];

    ll ch;
    ll k = 0;
    do {
        ch = 0;
        for (int i = 0; i < n; i++) {
            ll x = a[i]/n;
            ch += x;
            a[i] %= n;
            a[i] -= x;
        }
        for (int i = 0; i < n; i++)
            a[i] += ch;
        k += ch;
    } while (ch);

    cout << k << endl;
}
