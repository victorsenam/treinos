#include <bits/stdc++.h>
//#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define debug(...) {}
#endif

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 2e3;
const ll INF = 1e16;

int ts;
ll n, d;
ll h[N];
ll p[N*N], ps;
ll dp[2][2*N*N + N];

int main () {
    cin >> ts;
    while (ts--) {
        cin >> n >> d;

        for (int i = 0; i < n; i++) {
            cin >> h[i];
            p[i] = h[i];
        }
        ps = n;

        sort(p, p+n);

        for (int i = 0; i < n; i++) {
            for (int j = -n; j <= n; j++) {
                int to = h[i] + j*d;
                if (to < p[0] || to > p[n-1]) continue;
                p[ps++] = to;
            }
        }

        sort(p, p+ps);
        ps = unique(p, p+ps) - p;

        for (int i = 0; i < ps; i++) {
            dp[0][i] = INF;
            if (p[i] == h[0])
                dp[0][i] = 0;
        }

        for (int i = 1; i < n; i++) {
            multiset<ll> s;
            int l = 0, r = 0;
            for (int j = 0; j < ps; j++) {
                while (r < ps && abs(p[j] - p[r]) <= d) {
                    s.insert(dp[!(i&1)][r]);
                    r++;
                }
                while (l < r && abs(p[j] - p[l]) > d) {
                    s.erase(s.find(dp[!(i&1)][l]));
                    l++;
                }
                dp[i&1][j] = (*s.begin());
                dp[i&1][j] += abs(h[i] - p[j]);
                dp[i&1][j] = min(dp[i&1][j], INF);
            }
        }

        for (int i = 0; i < ps; i++) {
            if (p[i] == h[n-1]) {
                if (dp[!(n&1)][i] == INF)
                    cout << "impossible" << endl;
                else
                    cout << dp[!(n&1)][i] << endl;
            }
        }
    }
}
