#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 1e2+7;
const int mv[4][2] = {
    {0, 1},
    {0, -1},
    {1, 0},
    {-1, 0}
};

struct node {
    int i, j, k;
    ll d;

    bool operator < (const node & ot) const
    { return d > ot.d; }
};

int n, m;
ll mat[N][N];
ll dist[N][N][3], t;
int visi[N][N][3];

int main () {
    freopen("visitfj.in", "r", stdin);
    freopen("visitfj.out", "w", stdout);
    scanf("%d %lld", &n, &t);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%lld", &mat[i][j]);

    priority_queue<node> pq;
    node att;
    att.i = 0;
    att.j = 0;
    att.k = 0;
    dist[att.i][att.j][att.k] = att.d = 0;
    visi[att.i][att.j][att.k] = 1;
    pq.push(att);
    
    while (!pq.empty()) {
        att = pq.top(); pq.pop();

        if (visi[att.i][att.j][att.k] == 2) continue;
        visi[att.i][att.j][att.k] = 2;

        for (int k = 0; k < 4; k++) {
            node nxt = att;

            nxt.i += mv[k][0];
            nxt.j += mv[k][1];
            nxt.d += t;

            if (nxt.i < 0 || nxt.i >= n || nxt.j < 0 || nxt.j >= n) continue;

            nxt.k++;
            if (nxt.k == 3) {
                nxt.k = 0;
                nxt.d += mat[nxt.i][nxt.j];
            }
            
            if (!visi[nxt.i][nxt.j][nxt.k] || dist[nxt.i][nxt.j][nxt.k] > nxt.d) {
                visi[nxt.i][nxt.j][nxt.k] = 1;
                dist[nxt.i][nxt.j][nxt.k] = nxt.d;
                pq.push(nxt);
            }
        }
    }

    ll res = LLONG_MAX;
    for (int k = 0; k < 3; k++)
        if (visi[n-1][n-1][k])
            res = min(res, dist[n-1][n-1][k]);
    printf("%lld\n", res);
}
