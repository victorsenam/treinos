#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 32;

struct pos {
  int k,i,j;
  int dist;
};

int mv[6][3] = {
  {0,0,1},
  {0,0,-1},
  {0,1,0},
  {0,-1,0},
  {1,0,0},
  {-1,0,0}
};

int dist[N][N][N];
int n, m, l;
char mat[N][N][N];

int main () {
  while (scanf("%d %d %d", &l, &n, &m) != EOF) {
    if (!n) break;
    memset(dist, -1, sizeof dist);
    queue<pos> qu;
    for (int k = 0; k < l; k++) {
      for (int i = 0; i < n; i++) {
        scanf(" %s", mat[k][i]);
        for (int j = 0; j < m; j++) {
          if (mat[k][i][j] == 'S') {
            qu.push(pos({k,i,j}));
          }
        }
      }
    }

    int res = -1;
    while (!qu.empty()) {
      pos p = qu.front();
      qu.pop();

      // se eu tentei ir pra fora do grid, ignora
      if (p.k < 0 || p.k >= l) continue;
      if (p.i < 0 || p.i >= n) continue;
      if (p.j < 0 || p.j >= m) continue;

      // se eu já tinha chegado nessa posição antes, cheguei
      // com uma distância menor, então ignoro essa
      if (dist[p.k][p.i][p.j] != -1) continue;
      dist[p.k][p.i][p.j] = p.dist;

      // se eu entrei numa parede, ignora
      char c = mat[p.k][p.i][p.j];
      if (c == '#') continue;

      // se eu cheguei no fim, para de procurar
      if (c == 'E') {
        res = dist[p.k][p.i][p.j];
        break;
      }

      // olha pra todas as posições alcançáveis à
      // partir daqui
      for (int dir = 0; dir < 6; dir++) {
        pos nw = p;
        nw.k += mv[dir][0];
        nw.i += mv[dir][1];
        nw.j += mv[dir][2];
        nw.dist = p.dist + 1;
        qu.push(nw);
      }
    }

    if (res == -1) printf("Trapped!\n");
    else printf("Escaped in %d minute(s).\n", res);
  }
}
