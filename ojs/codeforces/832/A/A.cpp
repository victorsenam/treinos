#include <bits/stdc++.h>
#define debug if (1)

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

ll n, k;

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> k;
    
    n /= k;

    if (n&1)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
}
