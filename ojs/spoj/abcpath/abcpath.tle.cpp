#include <bits/stdc++.h>

using namespace std;

#define MAX 50

struct pos { int l, c; };

map<char, vector<pos> > mapa;
pos aux;
int m, n;
char linha[MAX];

bool adj(pos a, pos b) {
    int di, dj;
    di = a.l - b.l;
    if (di < 0) di = -di;
    dj = a.c - b.c;
    if (dj < 0) dj = -dj;
    
    if (di < 2 && dj < 2) return 1;
    return 0;
}

int busca(char a, pos p, int len) {
    int at, max = len;
    char nx = a + (char)1;

    if (at == 'Z') return len+1;

    for (int j = 0; j < mapa[nx].size(); j++) {
        if (adj(p, mapa[nx][j])) {

            at = busca(nx, mapa[nx][j], len+1);
            if (at > max) max = at;
            
        }
    }

    return max;
}

int main() {
    int max, at, c = 1;
    while (scanf("%d %d", &m, &n) != EOF && m && n) {
        max = 0;
        for (int i = 0; i < m; i++) {
            scanf(" %s", linha);
            for (int j = 0; j < n; j++) {
                aux.l = i;
                aux.c = j;
                mapa[linha[j]].push_back(aux);
            }
        }
        
        for (int i = 0; i < mapa['A'].size(); i++) {
            at = busca('A', mapa['A'][i], 1);
            if (at > max) max = at;
        }

        printf("Case %d: %d\n", c, max);
        c++;
        for (map<char, vector<pos> >::iterator i = mapa.begin(); i != mapa.end(); i++) {
            i->second.clear();
        }
        mapa.clear();
    }
}
                //printf("%c(%d,%d) %c(%d,%d)\n", a, mapa[a][i].l, mapa[a][i].c, nx, mapa[nx][j].l, mapa[nx][j].c);
