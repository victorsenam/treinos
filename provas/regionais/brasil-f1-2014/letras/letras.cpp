#include <bits/stdc++.h>
using namespace std;
#define MAX 100

int n, mat[MAX][MAX], dist[MAX][MAX], v, t, mini;
int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
struct pos {int x,y;};
queue<pos> fila;
pos init, p, q;

inline int intletra(char a) {
    if (a < 'a') return (int) (a - 'A');
    return (int) (a - 'a');
}

int main () {
    while(scanf("%d", &n) != EOF) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n ; j++) {
                scanf(" %c", &(mat[i][j]));
            }
        }
        init.x = init.y = 0;
        mini = -1;

        for (int mask = 0; mask < (1<<10); mask++) {
            v = intletra(mat[0][0]);
            t = mat[0][0] < 'a';
            if ((1&(mask>>v)) == t) continue;
            
            fila.push(init);

            for (int i = 0; i < n; i++) 
                    for (int j = 0; j < n; j++) 
                        dist[i][j] = -1;
            dist[0][0] = 1;

            while (!fila.empty()) {
                p = fila.front();
                fila.pop();

                if (p.x == n-1 && p.y == n-1) break;

                for (int i = 0; i < 4; i++) {
                    q.x = p.x + dx[i];
                    q.y = p.y + dy[i];

                    if (q.x >= n || q.x < 0 || q.y >= n || q.y < 0) continue;

                    v = intletra(mat[q.y][q.x]);
                    t = mat[q.y][q.x] < 'a';
                    if ((1&(mask>>v)) == t) continue;

                    if (dist[q.y][q.x] == -1) {
                        dist[q.y][q.x] = dist[p.y][p.x] + 1;
                        fila.push(q);
                    }
                }
            }
            while(!fila.empty()) fila.pop();

            if (mini == -1 || (dist[n-1][n-1] < mini && dist[n-1][n-1] != -1)) {
                mini = dist[n-1][n-1];
            }
        }
        printf("%d\n", mini);
    }
}
