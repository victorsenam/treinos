#include <bits/stdc++.h>

#define MAX 182

using namespace std;

queue<int> fila;
char    mat[MAX*MAX];
int     dist[MAX*MAX];
int     n, m, t;
int     dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};

void dfs() {
    int act, pos;

    while (!fila.empty()) {
        act = fila.front();
        fila.pop();

        for(int i = 0; i < 4; i++) {
            if (i%m+dx[i] < 0) continue;
            if (i%m+dx[i] >= m) continue;
            if (i/m+dy[i] < 0) continue;
            if (i/m+dy[i] >= n) continue;
            
            pos = i+dx[i]+dy[i]*m;

            if (dist[pos] == -1 || dist[pos] > dist[i] + 1) {
                fila.push(pos);
                dist[pos] = dist[i] + 1;
            }
        }
    }
}

int main () {
    scanf("%d", &t);

    while (t > 0) {
        scanf("%d %d", &n, &m);

        for (int i = 0; i < n*m; i++) {
            printf("%d\n", i);
            scanf(" %c", &mat[i]);
            if (mat[i] == '1') {
                fila.push(i);
                dist[i] = 0;
            } else dist[i] = -1;
        }

        dfs();

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                printf("%d ", dist[m*i+j]);
            }
            printf("\n");
        }

        t--;
    }

}
