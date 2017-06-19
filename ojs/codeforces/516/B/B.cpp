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

const int N = 2e3+7;
const int mv[4][2] = {
    {0,1},
    {1,0},
    {0,-1},
    {-1,0}
};

const char chr[4] = {'<','^','>','v'};

char mat[N][N];
int vl[N][N];
int n, m;

queue<pii> qu;

void fail () {
    cout << "Not unique" << endl;
    exit(0);
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int valid = 0;

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> mat[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (mat[i][j] == '*') continue;
            valid++;
            int r = 0;
            for (int k = 0; k < 4; k++) {
                int ni = i+mv[k][0], nj = j+mv[k][1];
                if (ni < 0 || ni >= n || nj < 0 || nj >= m) continue;
                if (mat[ni][nj] == '*') continue;
                r++;
            }
            vl[i][j] = r;
            if (r == 1)
                qu.push(pii(i,j));
        }
    }

    int r = 0;
    while (!qu.empty()) {
        pii ps = qu.front();
        int i = ps.first;
        int j = ps.second;
        qu.pop();
        
        if (mat[i][j] != '.') continue;

        bool ok = 0;
        for (int k = 0; k < 4; k++) {
            int ni = i+mv[k][0], nj = j+mv[k][1];
            if (ni < 0 || ni >= n || nj < 0 || nj >= m) continue;
            if (mat[ni][nj] != '.') continue;
            mat[i][j] = chr[k];
            mat[ni][nj] = chr[(k+2)%4];
            //cout << i << ',' << j << ' ' << ni << ',' << nj << endl;
            ok = 1;
            r += 2;

            for (int l = 0; l < 4; l++) {
                int ai = ni + mv[l][0];
                int aj = nj + mv[l][1];

                if (ai < 0 || ai >= n || aj < 0 || aj >= m) continue;
                if (mat[ai][aj] != '.') continue;

                vl[ai][aj]--;
                if (vl[ai][aj] == 1)
                    qu.push(pii(ai,aj));
            }
        }
    }

    if (r != valid)
        fail();

    for (int i = 0; i < n; i++) {
        cout << mat[i];
        cout << endl;
    }
}
