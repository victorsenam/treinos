#include <bits/stdc++.h>

#define MAX 100
#define INF 300

using namespace std;

typedef struct { int l; int c; } pos;

int n, m, t;
pos r, g1, g2, a, b;
queue<pos> fila;
int dist[MAX][MAX];
int dl[4] = {-1, 1, 0, 0}, dc[4] = {0, 0, -1, 1};

int main() {
    scanf("%d %d %d", &n, &m, &t);

    while (t--) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                dist[i][j] = INF;
            }
        }

        scanf("%d %d %d %d %d %d", &(r.l), &(r.c), &(g1.l), &(g1.c), &(g2.l), &(g2.c));
        fila.push(g1);
        fila.push(g2);
        dist[g1.l-1][g1.c-1] = 0;
        dist[g2.l-1][g2.c-1] = 0;

        while(!fila.empty()) {
            a = fila.front();
            fila.pop();

            for (int i = 0; i < 4; i++) {
                b.l = a.l+dl[i];
                b.c = a.c+dc[i];

                if (b.l < 1 || b.l > n) continue;
                if (b.l < 1 || b.c > m) continue;
                if (dist[b.c-1][b.c-1] <= dist[a.l-1][a.c-1] + 1) continue;
                
                dist[b.l-1][b.c-1] = dist[a.l-1][a.c-1] + 1;
                fila.push(b);
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                printf("%d ", dist[i][j]);
            }
            printf("\n");
        }

        if (dist[r.l-1][0] > r.c-1 || dist[0][r.c-1] > r.l-1 || dist[r.l-1][m-1] > n-r.c || dist[n-1][r.c-1] > m-r.l) printf("YES\n");
        else printf("NO\n");
    }
}
