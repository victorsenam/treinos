#include <bits/stdc++.h>

using namespace std;

const int N = 103;
const int F = 11;
const int S = 3334;

struct posi {
    int f, i, j;
};

const int di[4] = {1, -1, 0, 0};
const int dj[4] = {0, 0, -1, 1};

posi ps[N];
char mat[F][N][N];
int dist[F][N][N];
int t, f, h, w, n, s;
int costo[N];
int val[N];
int vis[N][S];
int memo[N][S];
queue<posi> q;
int turn;
posi att, aux;

int solve (int i, int s) {
    if (i == n)
        return 0;

    int & me = memo[i][s];

    if (vis[i][s] == turn)
        return me;
    vis[i][s] = turn;

    me = solve(i+1, s);
    if (costo[i] >= 0 && costo[i] <= s)
        me = max(me, solve(i+1, s-costo[i]) + val[i]);

    return me;
}

void upd (posi a, posi b) {
    if (a.f >= f || a.f < 0)
        return;
    if (a.i >= h || a.i < 0)
        return;
    if (a.j >= w || a.j < 0)
        return;
    if (mat[a.f][a.i][a.j] == 'X')
        return;

    if (dist[a.f][a.i][a.j] == -1 || dist[a.f][a.i][a.j] > dist[b.f][b.i][b.j] + 1) {
        dist[a.f][a.i][a.j] = dist[b.f][b.i][b.j] + 1;
        q.push(a);
    }
}

int main () {
    scanf("%d", &t);

    while (t--) {
        scanf("%d %d %d %d %d", &f, &h, &w, &n, &s);

        for (int k = 0; k < f; k++) {
            for (int i = 0; i < h; i++) {
                scanf(" %s", mat[k][i]);
                for (int j = 0; j < w; j++) {
                    dist[k][i][j] = -1;
                    if (mat[k][i][j] == 'S') {
                        aux.f = k;
                        aux.i = i;
                        aux.j = j;
                    }
                }
            }
        }
        
        while (!q.empty()) q.pop();
        q.push(aux);
        dist[aux.f][aux.i][aux.j] = 0;

        while (!q.empty()) {
            att = q.front();
            q.pop();
            char c = mat[att.f][att.i][att.j];

            if (c == 'U') {
                aux = att;
                aux.f++;
                upd(aux, att);
            } else if (c == 'D') {
                aux = att;
                aux.f--;
                upd(aux, att);
            } 
            for (int k = 0; k < 4; k++) {
                aux = att;
                aux.i += di[k];
                aux.j += dj[k];
                upd(aux, att);
            }
        }

        for (int i = 0; i < n; i++) {
            scanf("%d %d %d %d", &aux.f, &aux.i, &aux.j, val+i);
            aux.f--;
            aux.i--;
            aux.j--;
            costo[i] = dist[aux.f][aux.i][aux.j];
        }

        s /= 3;

        turn++;
        printf("%d\n", solve(0, s));
    }
}
