#include <bits/stdc++.h>

#define MAX 501

int tab[MAX][MAX];

int main () {
    int t = 1;
    int w, h, n, op, ax, ay, bx, by, aux;

    for (int i = 0; i < MAX; i++)
        for (int j = 0; j < MAX; j++)
            tab[i][j] = 0;

    while(scanf("%d %d %d", &w, &h, &n) != EOF) {
        if (!w && !h && !n) break;
        
        op = w*h;

        for (int k = 0; k < n; k++) {
            scanf("%d %d %d %d", &ax, &ay, &bx, &by);

            if (bx < ax) {
                aux = ax;
                ax = bx;
                bx = aux;
            }
            if (by < ay) {
                aux = ay;
                ay = by;
                by = aux;
            }

            for (int i = ax; i <= bx; i++) {
                for (int j = ay; j <= by; j++) {
                    if (tab[i][j] != t) {
                        op--;
                        tab[i][j] = t;
                    }
                }
            }
        }
        if (op == 0) printf("There is no empty spots.\n");
        else if (op == 1) printf("There is one empty spot.\n");
        else printf("There are %d empty spots.\n", op);

        t++;
    }
}

