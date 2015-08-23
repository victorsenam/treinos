#include <bits/stdc++.h>

using namespace std;

struct local {
    int l, c;
};

int tab[8][8], dc[8] = {1, 2, 2, 1, -1, -2, -2, -1}, dl[8] = {2, 1, -1, -2, -2, -1, 1, 2};
char auxac, auxal, auxbc, auxbl, lco = '1', cco = 'a';
local posi, posf, posa, posn;
queue<local> fila;

void printmat (int mat[8][8]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

int main () {
    while (scanf(" %c%c %c%c", &auxac, &auxal, &auxbc, &auxbl) != EOF) {
        posi.c = (int) auxac - cco;
        posi.l = (int) auxal - lco;
        posf.c = (int) auxbc - cco;
        posf.l = (int) auxbl - lco;

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                tab[i][j] = 0;
            }
        }

        while(!fila.empty()) fila.pop();

        if (posi.c == posf.c && posi.l == posf.l);
        else fila.push(posi);

        while(!fila.empty()) {
            int i;
            posa = fila.front();
            fila.pop();
            // printf("%d %d\n", posa.c, posa.l);

            for (i = 0; i < 8; i++) {
                posn.c = posa.c + dc[i];
                posn.l = posa.l + dl[i];

                if (posn.c >= 8 || posn.c < 0) continue;
                if (posn.l >= 8 || posn.l < 0) continue;

                if (tab[posn.c][posn.l] > 0) continue;

                tab[posn.c][posn.l] = tab[posa.c][posa.l] + 1;
                if (posn.c == posf.c && posn.l == posf.l) break;
                fila.push(posn);
            }
            // printmat(tab);

            if (i < 8) break;
        }
        
        printf("To get from %c%c to %c%c takes %d knight moves.\n", auxac, auxal, auxbc, auxbl, tab[posf.c][posf.l]);
    }
}
