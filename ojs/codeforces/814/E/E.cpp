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

const int N = 51;
const ll MOD = 1e9+7;

inline ll mod (ll x) {
    return x%MOD;
}

int n;
int d[N];
int ac[N][4];
ll memo[2][N][N][N][N];
ll comb[N][N];

int main () {
    memset(memo, -1, sizeof memset);
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    cin >> d[0];

    int cn[2] = {0,0};
    for (int i = 1; i <= d[0]; i++) {
        cin >> d[i];
        cn[d[i]-2]++;
    }

    comb[0][0] = 1;
    for (int a2 = 0; a2 < N; a2++) {
        for (int a1 = 0; a1 < N; a1++) {
            ll & me = comb[a1][a2];
            if (a2) {
                if (a1 >= 2) // 2 pra 1
                    me = mod(me + comb[a1-2][a2-1] * a1 * (a1 - 1) / 2);
                if (a1 >= 1 && a2 > 1) // 1 pra cada
                    me = mod(me + comb[a1][a2-2] * a1 * (a2 - 1));
                if (a2 > 2) // 2 pra 2
                    me = mod(me + comb[a1+2][a2-3] * (a2 - 1) * (a2 - 2) / 2);
            } else {
                if (a1 > 1)
                    me = mod(me + (a1-1) * memo[a1-2][a2]);
            }
        }
    }

    memo[d[0]&1][cn[0]][cn[1]][0][0] = 1;

    for (int i = d[0]+1; i < n; i++) {
        cin >> d[i];

        for (int att = 0; att < N*N; att++) {
            int a[3] = {3,att/N,att%N};
            for (int cur = 0; cur < N*N; cur++) {
                int c[3] = {3,cur/N,cur%N};
                    
                ll & me = memo[i&1][a[1]][a[2]][c[1]][c[2]];

                for (int use = 1; use <= d[i]; use++) {
                    if (!c[d[i] - use]) continue;
                    c[d[i] - use]--;
                    for (int t1 = 0; t1 <= use; t1++) {
                        if (a[1] < t1) continue;
                        if (a[2] < use - t1) continue;

                        a[1] -= t1;
                        a[2] -= use - t1;

                        me = mod(me + memo[!(i&1)][a[1]][a[2]][c[1]][c[2]] * choose(a[1]+t1,t1) * choose(a[2]+use-t1,use-t1));

                        a[1] += t1;
                        a[2] += use - t1;
                    }
                    c[d[i] - use]++;
                }
            }

            for (int cur = 0; cur < N*N; cur++) {
                int c[3] = {3,cur/N,cur%N};

                ll & me = memo[i&1][c[1]][c[2]][0][0];
                me = mod(me + memo[!(i&1)][a[1]][a[2]][c[1]][c[2]] * comb[a[1]][a[2]]);
            }
        }
    }
}
