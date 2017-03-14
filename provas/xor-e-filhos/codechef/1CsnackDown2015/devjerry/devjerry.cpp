#include <bits/stdc++.h>

using namespace std;
typedef int num;
#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#else
#define debug(...) //
#endif

#define N 20

queue<pair<int, int> > q;
int n, t;
int sx, sy, ex, ey, bx, by;
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
int dist[N][N], ds;
pair<int, int> aux;
int nx, ny;

int main () 
{
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        scanf("%d %d %d %d %d %d", &sx, &sy, &ex, &ey, &bx, &by);
        sx--; sy--; ex--; ey--; bx--; by--;

        while (!q.empty()) q.pop();

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                dist[i][j] = -1;

        q.push(make_pair(sx, sy));
        dist[sx][sy] = 0;
        while (!q.empty()) {
            aux = q.front();
            ds = dist[aux.first][aux.second];
            q.pop();

            for (int i = 0; i < 4; i++) {
                nx = aux.first + dx[i];               
                ny = aux.second + dy[i];

                if (nx < 0 || nx >= n) continue;
                if (ny < 0 || ny >= n) continue;
                if (nx == bx && ny == by) continue;
                if (dist[nx][ny] > -1) continue;
                
                dist[nx][ny] = ds+1;

                if (nx == ex && ny == ey) {
                    printf("%d\n", ds+1);
                    while (!q.empty()) q.pop();
                    break;
                }

                q.push(make_pair(nx, ny));
            }
        }
    }
}
