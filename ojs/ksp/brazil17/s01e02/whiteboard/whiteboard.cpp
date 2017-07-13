#include <bits/stdc++.h>
#define debug if (1)

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 2e6+7;

struct evt {
    int l, r;
    ll tm, x, y;

    bool operator < (const evt & ot) const {
        return tm < ot.tm;
    }
};
ostream & operator << (ostream & os, const evt & o) {
    return os << "[" << o.l << ".." << o.r << "]" << o.tm;
}

int n, m;
char inp[N];
ll mat[N];
vector<evt> occ[2][N]; // 1: coluna fixa, 0: linha fixa
int cur[2][N];
priority_queue<evt> pq[2][N];

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int qs;
    cin >> n >> m >> qs;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> inp[i*m + j];

    
    int i = n-1, j = 0;
    ll tm = 0;
    for (int tt = 1; tt <= qs; tt++) {
        string cm;
        ll qt;
        evt cur;
        cur.tm = tm;
        cur.x;

        cin >> cm >> qt;

        if (cm[0] == 'u') {
            cur.l = i - qt;
            cur.r = i;
            cur.x = tm + qt;
            cur.y = -1;
            i -= qt;
            occ[1][j].push_back(cur);
        } else if (cm[0] == 'd') {
            cur.l = i;
            cur.r = i + qt;
            cur.x = tm;
            cur.y = 1;
            i += qt;
            occ[1][j].push_back(cur);
        } else if (cm[0] == 'r') {
            cur.l = j;
            cur.r = j + qt;
            cur.x = tm;
            cur.y = 1;
            j += qt;
            occ[0][i].push_back(cur);
        } else {
            cur.l = j - qt;
            cur.r = j;
            cur.x = tm + qt;
            cur.y = -1;
            j -= qt;
            occ[0][i].push_back(cur);
        }

        tm += qt;
    }

    for (int i = 0; i < n; i++) {
        sort(occ[0][i].begin(), occ[0][i].end(), [] (evt a, evt b) {
            return a.l < b.l;
        });
    }
    for (int j = 0; j < m; j++) {
        sort(occ[1][j].begin(), occ[1][j].begin(), [] (evt a, evt b) {
            return a.l < b.l;
        });
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            while (cur[0][i] < occ[0][i].size() && occ[0][i][cur[0][i]].l <= j) {
                pq[0][i].push(occ[0][i][cur[0][i]++]);
            }
            while (cur[1][j] < occ[1][j].size() && occ[1][j][cur[1][j]].l <= i) {
                pq[1][j].push(occ[1][j][cur[1][j]++]);
            }

            while (!pq[0][i].empty() && pq[0][i].top().r < j) {
                pq[0][i].pop();
            }
            while (!pq[1][j].empty() && pq[1][j].top().r < i) {
                pq[1][j].pop();
            }
            
            ll & vl = mat[i*m + j];
            vl = 0;
            if (!pq[0][i].empty()) {
                vl = max(vl, pq[0][i].top().x + pq[0][i].top().y*abs(j - pq[0][i].top().l) + 1ll);
            }
            if (!pq[1][j].empty()) {
                vl = max(vl, pq[1][j].top().x + pq[1][j].top().y*abs(i - pq[1][j].top().l) + 1ll);
            }
        }
    }

    ll l = 0;
    ll r = tm + 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if ((inp[i*m+j] == '#') && (mat[i*m+j] == 0)) {
                cout << "-1 -1" << endl;
                return 0;
            } else if (inp[i*m+j] == '#') {
                l = max(l, mat[i*m+j]);
            } else if (mat[i*m+j]) {
                r = min(r, mat[i*m+j]-1);
            }
        }
    }

    cout << l << " " << r << endl;
}
