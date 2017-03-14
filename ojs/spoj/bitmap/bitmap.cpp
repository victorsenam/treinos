#include <bits/stdc++.h>

#define MAX 184

using namespace std;

char mat[MAX][MAX];
int n, m, t, at, atc, atl, pc, pl;
int dc[4] = {-1, 1, 0, 0}, dl[4] = {0, 0, -1, 1};
int diff[MAX][MAX];
queue<int> fila;

int main () {
    scanf("%d", &t);

    while ( t > 0 ) {
        scanf("%d %d", &n, &m);
        for (int i = 0 ; i < n; i++) {
            scanf(" %s", &mat[i]);
            for (int j = 0; j < m; j++) {
                if (mat[i][j] == '1') {
                    diff[i][j] = 0;
                    fila.push(i*m+j);
                } else diff[i][j] = -1;
            }
        }

        while(!fila.empty()) {
            at = fila.front();
            fila.pop();
            atc = at%m;
            atl = at/m;
            
            for (int i = 0; i < 4; i++) {
                pc = atc + dc[i];
                pl = atl + dl[i];

                if (pc < 0 || pc >= m) continue;
                if (pl < 0 || pl >= n) continue;

                if (diff[pl][pc] == -1 || diff[pl][pc] > diff[atl][atc] + 1) {
                    diff[pl][pc] = diff[atl][atc] + 1;
                    fila.push(pl*m+pc);
                }
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                printf("%d ", diff[i][j]);
            }
            printf("\n");
        }

        t--;
    }
}
