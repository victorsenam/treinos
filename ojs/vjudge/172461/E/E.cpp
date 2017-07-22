#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

int h[1123], w[1123];

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int i, n, t;
    cin >> t;
    while(t--) {
        cin >> n;
        for(i = 0; i < n; i++)
            cin >> w[i];
        for(i = 0; i < n; i++)
            cin >> h[i];
        sort(h, h + n, greater<int>());
        int mx = w[0] * h[0];
        sort(w + 1, w + n);
        for(i = 1; i < n; i++)
            if(w[i] * h[i] >= mx)
                break;
        if(i < n) puts("NO");
        else puts("YES");
    }
}
