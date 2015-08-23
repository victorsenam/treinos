#include <bits/stdc++.h>

typedef struct {
    int p, d;
} frase;

std::vector<frase> v;
int s, w, c, t, memo[51][1001];
frase aux;

int max (int a, int b) {
    if (a > b) return a;
    return b;
}

int preenche (int i, int f) {
    int r;
    if (f <= 0 || i >= w) return 0;
    if (memo[i][f] != -1) return memo[i][f];

    if (f >= v[i].p) r = max(preenche(i+1, f-v[i].p)+v[i].d, preenche(i+1, f));
    else r = preenche(i+1, f);

    memo[i][f] = r;
 //   printf("(%d,%d) -> %d\n", i, f, r);
    return r;
}

int main () {
    t = 0;
    while (scanf("%d %d", &s, &w) != EOF && s && w) {
        t++;

        v.clear();
        for (int i = 0; i < w; i++) {
            scanf("%d %d", &(aux.p), &(aux.d));
            v.push_back(aux);
            for (int j = 0; j <= s; j++) {
                memo[i][j] = -1;
            }
        }

        printf("Teste %d\n%d\n\n", t, preenche(0, s));
    }
}
