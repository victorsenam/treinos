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

ll mx[2][N];
ll mat[N][N];
int n, m;
ll res;
int p[2][N];

int visi[N];
int ass[N];

bool dfs (int i, int k) {
    if (visi[i] == k)
        return false;
    visi[i] = k;

    for (int j = 0; j < m; j++) {
        if (mx[0][i] != mx[1][j]) continue;
        if (mat[i][j] == 0) continue;

        if (ass[j] == -1 || dfs(ass[j], k)) {
            ass[j] = i;
            return true;
        }
    }
    return false;
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    memset(visi, -1, sizeof visi);
    memset(ass, -1, sizeof ass);

    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> mat[i][j];
            mx[0][i] = max(mx[0][i], mat[i][j]);
            mx[1][j] = max(mx[1][j], mat[i][j]);

            res += max(mat[i][j] - 1, 0ll);
        }
    }

    for (int i = 0; i < n; i++)
        res -= max(mx[0][i] - 1, 0ll);
    for (int j = 0; j < m; j++)
        res -= max(mx[1][j] - 1, 0ll);

    for (int i = 0; i < n; i++) {
        if (dfs(i,i))
            res += max(mx[0][i] - 1, 0ll);
    }

    cout << res << endl;
}
