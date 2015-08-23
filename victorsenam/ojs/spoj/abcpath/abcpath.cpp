#include <bits/stdc++.h>

using namespace std;

#define MAX 50

struct pos { int l, c; };

int dl[8] = {1, 1, 1, 0, 0, -1, -1, -1}, dc[8] = {1, 0, -1, 1, -1, 1, 0, -1};
pos aux;
int m, n;
char linha[MAX][MAX];
int memo[MAX][MAX];
vector<pos> as;

int busca(char a, pos p) {
    int at, max = 0;
    char nc = a + (char)1;
    pos np;
    

    if ((p.l) < 0 || (p.l) >= m || (p.c) < 0 || (p.c) >= n) return 0;
    if (linha[p.l][p.c] != a) return 0;
    if (memo[p.l][p.c] != -1) return memo[p.l][p.c];
    for (int i = 0; i < 8; i++) {
        np.l = p.l + dl[i];
        np.c = p.c + dc[i];
        at = busca(nc, np);
        if (at > max) max = at;
    }
    memo[p.l][p.c] = max + 1;
    return max + 1;
}

int main() {
    int max, at, c = 1, topo;
    char sup;
    while (scanf("%d %d", &m, &n) != EOF && m && n) {
        max = 0;
        sup = 'A';
        for (int i = 0; i < m; i++) {
            scanf(" %s", linha[i]);
            for (int j = 0; j < n; j++) {
                memo[i][j] = -1;
                if (linha[i][j] == 'A') {
                    aux.l = i;
                    aux.c = j;
                    as.push_back(aux);
                }
                if (linha[i][j] > sup) sup = linha[i][j];
            }
        }
        for (int i = 0; i < as.size(); i++) {
            at = busca('A', as[i]);
            if (at > max) max = at;
        }

        printf("Case %d: %d\n", c, max);
        c++;
    }

}
