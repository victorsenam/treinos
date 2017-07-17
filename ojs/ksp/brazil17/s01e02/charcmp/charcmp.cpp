#include <bits/stdc++.h>
#define debug if (1)

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e2+8;
const int mv[8][2] = {
    {1,0},
    {0,1},
    {-1,0},
    {0,-1},
    {1,1},
    {1,-1},
    {-1,-1},
    {-1,1}
};

char mat[2][N][N];
int vis[2][N][N];
int cmp[2][N][N];
int n[2], m[2];
int p[2][N], deg[2][N], ps[2];
multiset<int> s[2][N];
map<multiset<int>, int> mp;
int r[2];

void dfs (int k, int i, int j, int c) {
    if (cmp[k][i][j] != -1)
        return;
    cmp[k][i][j] = c;
    
    for (int d = 0; d < 4 + 4*(mat[k][i][j] == '#'); d++) {
        int ni = i+mv[d][0];
        int nj = j+mv[d][1];

        if (ni < 0 || ni >= n[k] || nj < 0 || nj >= m[k]) {
            p[k][c] = min(p[k][c], 0);
        } else if (mat[k][i][j] != mat[k][ni][nj]) {
            if (cmp[k][ni][nj] != -1)
                p[k][c] = min(p[k][c], cmp[k][ni][nj]);
        } else {
            dfs(k, ni, nj, c);
        }
    }
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    while (true) {
        for (int k = 0; k < 2; k++) {
            cin >> n[k] >> m[k];
            if (n[k] + m[k] == 0) return 0;

            for (int i = 0; i < n[k]; i++) {
                cin >> mat[k][i];
                for (int j = 0; j < m[k]; j++) {
                    cmp[k][i][j] = -1;
                    vis[k][i][j] = 0;
                }
            }

            p[k][0] = -1;
            for (int i = 0; i < n[k]; i++) {
                if (mat[k][i][0] == '.')
                    dfs(k, i, 0, 0);
                if (mat[k][i][m[k]-1] == '.')
                    dfs(k, i, m[k]-1, 0);
            }
            for (int i = 0; i < m[k]; i++) {
                if (mat[k][0][i] == '.')
                    dfs(k, 0, i, 0);
                if (mat[k][n[k]-1][i] == '.')
                    dfs(k, n[k]-1, i, 0);
            }

            ps[k] = 1;
            for (int i = 0; i < n[k]; i++)
                for (int j = 0; j < m[k]; j++)
                    if (cmp[k][i][j] == -1) {
                        p[k][ps[k]] = ps[k];
                        deg[k][ps[k]] = 0;
                        s[k][ps[k]].clear();
                        if (mat[k][i][j] == '#')
                            s[k][ps[k]].insert(-1);
                        dfs(k, i, j, ps[k]++);
                    }

            for (int i = 1; i < ps[k]; i++)
                deg[k][p[k][i]]++;
            queue<int> qu;
            for (int i = 0; i < ps[k]; i++)
                if (!deg[k][i])
                    qu.push(i);

            int qt = 0;
            while (!qu.empty()) {
                int u = qu.front();
                qu.pop();
                    
                int cr;
                if (mp.find(s[k][u]) == mp.end()) {
                    cr = mp[s[k][u]] = qt++;
                } else {
                    cr = mp[s[k][u]];
                }

                if (!u) {
                    r[k] = cr;
                } else {
                    s[k][p[k][u]].insert(cr);
                }
            }
        }

        if (r[0] == r[1])
            cout << "yes" << endl;
        else
            cout << "no" << endl;

    }
}
