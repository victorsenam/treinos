#include <bits/stdc++.h>

#define MAX 1001

using namespace std;

queue<int>  fila;
int         dist[MAX];
int         movs[10];
int         t, aux, m, next;

void bfs() {
    while (!fila.empty()) {
        aux = fila.front();
        fila.pop();

        for (int i = 0; i < m; i++) {
            next = aux+movs[i];
            if (next < 0 || next > 1000) continue;
            if (next == 100) {
                dist[100] = dist[aux] + 1;
                return;
            }
            if (!dist[next]) {
                dist[next] = dist[aux] + 1;
                fila.push(next);
            }
        }
    }
}

int main () {
    while (scanf("%d", &m) != EOF && m) {
        for (int i = 0; i < MAX; i++) {
            dist[i] = 0;   
        }
        for (int i = 0; i < m; i++) {
            scanf("%d", &movs[i]);
            dist[movs[i]] = 1;
            fila.push(movs[i]);
        }
        for (int i = 0; i < m; i++) {
            scanf("%d", &aux);
            movs[i] = movs[i] - aux;
        }
        bfs();
        if (dist[100]) printf("%d\n", dist[100]);
        else printf("cavaleiro morreu\n");

        while(!fila.empty()) fila.pop();
    }

}
