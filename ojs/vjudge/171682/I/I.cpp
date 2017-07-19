#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 112345;

char s[N];
int nx[N], dr[N], dl[N], pr[N];

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t, i, n, k;
    cin >> t;
    while(t--) {
        cin >> n >> k;
        cin >> s;
        nx[n - 1] = n;
        dr[n] = 0;
        dr[n - 1] =  1;
        for(i = n - 2; i >= 0; i--) {
            if(s[i] != s[i + 1])
                nx[i] = i + 1;
            else
                nx[i] = nx[i + 1];
            if(nx[i] - i <= k) dr[i] = dr[nx[i]] + 1;
            else dr[i] = dr[i + k] + 1;
        }
        pr[0] = -1;
        dl[0] = 1;
        for(i = 1; i < n; i++) {
            if(s[i] != s[i - 1])
                pr[i] = i - 1;
            else
                pr[i] = pr[i - 1];
            if(i - pr[i] <= k) dl[i] = (pr[i] == -1? 0 : dl[pr[i]]) + 1;
            else dl[i] = (i == k? 0 : dl[i - k]) + 1;
        }
        ll mn = LLONG_MAX;
        for(i = 0; i <= n - k; i++) {
            if(nx[i] - i < k) continue;
            mn = min<ll>(mn, 1 + (i? dl[i - 1] : 0) + dr[i + k]);
        }
        if(mn == LLONG_MAX) mn = -1;
        cout << mn << '\n';
    }
}
