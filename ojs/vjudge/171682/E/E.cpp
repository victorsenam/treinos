#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

const int N = 412;
const int M = 11234;

int n;
int bad[M], tr[M][2], go[M][2], f[M], en;

ll memo[N][M];
ll solve(int i, int v) {
    if(bad[v]) return 0;
    if(i == n) return 1;
    ll &r = memo[i][v];
    if(r != -1) return r;
    r = mod(solve(i + 1, go[v][0]) + solve(i + 1, go[v][1]));
    return r;
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int i, t, k, j;
    cin >> t;
    while(t--) {
        cin >> n >> k;
        vector<string> pal;
        for(int g = k; g <= k + 1; g++)
            for(i = 0; i < (1 << g); i++) {
                string s;
                for(j = 0; j < g; j++)
                    if((i >> j) & 1)
                        s.pb('1');
                    else
                        s.pb('0');
                string s2 = s;
                reverse(s2.begin(), s2.end());
                if(s == s2) pal.pb(s);
            }
        en = 1;
        for(string s : pal) {
            int v = 0;
            for(char c : s) {
                if(tr[v][c - '0'] == 0) tr[v][c - '0'] = en++;
                v = tr[v][c - '0'];
            }
            bad[v] = true;
        }
        queue<int> q;
        for(int g = 0; g <= 1; g++)
            go[0][g] = tr[0][g];
        for(int g = 0; g <= 1; g++)
            if(tr[0][g])
                q.push(tr[0][g]), f[tr[0][g]] = 0;
        while(!q.empty()) {
            int v = q.front(); q.pop();
            bad[v] = bad[v] || bad[f[v]];
            for(int g = 0; g <= 1; g++)
                if(tr[v][g]) {
                    go[v][g] = tr[v][g];
                    q.push(tr[v][g]);
                    int &F = f[tr[v][g]];
                    F = f[v];
                    while(F && !tr[F][g])
                        F = f[F];
                    if(tr[F][g])
                        F = tr[F][g];
                } else {
                    go[v][g] = go[f[v]][g];
                }
        }
        for(i = 0; i < n; i++)
            for(j = 0; j < en; j++)
                memo[i][j] = -1;
        cout << solve(0, 0) << '\n';
        for(i = 0; i < en; i++)
            tr[i][0] = tr[i][1] = bad[i] = 0;
    }
}
