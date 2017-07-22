#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back


const int N = 1e6;
int n, k;
ll v[N];
ll res;

int main () {
    cin >> n >> k;
    
    for (int i = 0; i < n; i++)
        cin >> v[i];

    ll cur = 0;

    ll a = 0, b = 0;
    ll ba = 0;
    for (int i = 0; i < k && i < n; i++)
        b += v[i];
    res = b;

    for (int i = k; i < n; i++) {
        if (i-2*k >= 0) {
            a -= v[i-2*k];
        }
        a += v[i-k];
        ba = max(ba, a);
        b += v[i] - v[i-k];
        res = max(b + ba, res);
    }
    cout << res << endl;
}
