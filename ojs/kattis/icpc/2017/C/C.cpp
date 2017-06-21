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

const int N = 103;

ll mat[2][N];
ll val[N][N];
int p[N*N];
int n, m;

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;

    ll res = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            ll a;
            cin >> a;
            val[i][j] = a;
            res += a - !!a;
            mat[0][i] = max(mat[0][i], a);
            mat[1][j] = max(mat[1][j], a);
            p[i*m+j] = i*m+j;
        }
    }

    sort(p, p+n*m, [] (int a, int b) { return val[a/m][a%m] < val[b/m][b%m]; });

    for (int pp = 0; pp < n*m; pp++) {
        int i = p[pp]/m;
        int j = p[pp]%m;
        if (mat[0][i] == mat[1][j] && val[i][j] && mat[0][i] > 0) {
            res -= mat[0][i] - 1;
            mat[0][i] = mat[1][j] = -1;
        }
    }

    for (int i = 0; i < n; i++) {
        if (mat[0][i] <= 0)
            continue;
        res -= mat[0][i] - 1;
    }
    for (int i = 0; i < m; i++) {
        if (mat[1][i] <= 0)
            continue;
        res -= mat[1][i] - 1;
    }

    cout << res << endl;
}
