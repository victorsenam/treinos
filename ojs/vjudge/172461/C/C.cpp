#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 300;
const int M = 1e6;
const ll MOD = 1e9+7;

int n, m;
ll deg[N];
ll adj[N][N];
int v[M][2];
ll dp[2][4][4];

ll choose (ll a, ll b) {
    ll r = 1;
    for (int i = 0; i < b; i++)
        r *= (a-i);
    for (int i = 1; i <= b; i++)
        r /= i;
    return r;
}

ll mod (ll x) {
    return x%MOD;
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        cin >> v[i][0] >> v[i][1];
        v[i][0]--; v[i][1]--;
        deg[v[i][0]]++; deg[v[i][1]]++;
        adj[v[i][0]][v[i][1]] = adj[v[i][1]][v[i][0]] = 1;
    }

    ll res = 0;
    for (int i = 0; i < m; i++)  {
        int a = v[i][0], b = v[i][1];

        for (int x = 0; x <= 3; x++)
            for (int y = 0; y <= 3; y++)
                dp[1][x][y] = 0;
        dp[1][0][0] = 1;

        for (int j = 0; j < n; j++) {
            for (int x = 0; x <= 3; x++) {
                for (int y = 0; y <= 3; y++) {
                    dp[j&1][x][y] = dp[!(j&1)][x][y];

                    if (j == a || j == b) continue;
                    if (x && adj[a][j])
                        dp[j&1][x][y] = mod(dp[j&1][x][y] + dp[!(j&1)][x-1][y]);
                    if (y && adj[b][j])
                        dp[j&1][x][y] = mod(dp[j&1][x][y] + dp[!(j&1)][x][y-1]);
                }
            }
        }

        res = mod(res + dp[!(n&1)][2][3] + dp[!(n&1)][3][2]);
    }
    cout << res << endl;
}
