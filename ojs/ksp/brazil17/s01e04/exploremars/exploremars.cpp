#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;

const int N = 1e3+7;

const int mv[4][2] = {
    {-1,0},
    {0,1},
    {1,0},
    {0,-1}
};

int n, m;
char mat[N][N];
int visi[N][N], vs, tr;
int dist[N][N];
int cm[N][N], cs;
int qt[N*N], dn[N*N];
vector<pii> res;
vector<int> tim;

ll mod (ll a, ll b) {
    return ((a%b) + b)%b + b;
}

int get (char k) {
    k = tolower(k);
    if (k == 'n')
        return 0;
    if (k == 'e')
        return 1;
    if (k == 's')
        return 2;
    return 3;
}

int dfs (int i, int j) {
    if (visi[i][j]) {
        if (visi[i][j] < tr)
            return 0;
        dist[i][j] = 0;
        return vs - visi[i][j];
    }
    visi[i][j] = vs++;

    int d = get(mat[i][j]);
    int rr = dfs(i+mv[d][0],j+mv[d][1]);
    int ni = i+mv[d][0], nj = j+mv[d][1];
    if (i != ni || j != nj)
        dist[i][j] = dist[ni][nj] + 1;
    return rr;
    
}

int jn (int i, int j) {
    if (cm[i][j] == -1)
        cm[i][j] = cs++;
    if (cm[i][j])
        return cm[i][j];
    cm[i][j] = -1;
    
    int d = get(mat[i][j]);
    return cm[i][j] = jn(i+mv[d][0],j+mv[d][1]);
}

int main () {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> mat[i];
    }

    memset(qt, -1, sizeof qt);
    cs = 1;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            jn(i,j);

    vs++;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            tr = vs;
            if (mat[i][j] >= 'A' && mat[i][j] <= 'Z') {
                if (qt[cm[i][j]] == -1)
                    qt[cm[i][j]] = dfs(i,j);
                else
                    dfs(i,j);

                if (dn[cm[i][j]] == qt[cm[i][j]]) continue;

                res.push_back(pii(i,j));
                tim.push_back(mod(dn[cm[i][j]] - dist[i][j] + qt[cm[i][j]], qt[cm[i][j]]));

                dn[cm[i][j]]++;
            }
        }
    }

    cout << res.size() << endl;
    for (int i = 0; i < res.size(); i++)
        cout << res[i].first + 1 << " " << res[i].second + 1 << " " << tim[i] << endl;
}
