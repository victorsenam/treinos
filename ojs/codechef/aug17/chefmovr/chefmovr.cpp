#include <bits/stdc++.h>
#define debug if (1)

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e6+7;
int n, d, ts;
ll v[N];

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> ts;
    while (ts--) {
        cin >> n >> d;
        ll obj = 0;
        for (int i = 0; i < n; i++) {
            cin >> v[i];
            obj += v[i];
        }
        
        ll rs = 0;
        if (obj%n)
            rs = -1;
        obj /= n;

        for (int i = 0; rs >= 0 && i + d < n; i++) {
            ll hs = obj - v[i];

            rs += abs(hs);
            v[i] += hs;
            v[i+d] -= hs;
        }

        for (int i = n-d; rs >= 0 && i < n; i++)
            if (v[i] != obj)
                rs = -1;

        cout << rs << endl;
    }
}
