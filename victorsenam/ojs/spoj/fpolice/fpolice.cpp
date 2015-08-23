#include <bits/stdc++.h>

using namespace std;

#define MAX 100

int maxt, minr, mint, n, t;
int tims[MAX][MAX], riss[MAX][MAX];

void busca (int risk, int time, int orig) {
    if (time > maxt) return;
    if (minr && risk > minr) return;
    if (orig == n-1) {
        if (mint && risk == minr && time < mint) return;
        minr = risk;
        mint = time;
    }
    for (int i = n-1; i >= 0; i--)
        if (i != orig) busca(risk + riss[orig][i], time + tims[orig][i], i);
}

int main () {
    scanf("%d", &t);
    while (t--) {
        scanf("%u %u", &n, &maxt);

        for (int i = 0; i < n; i++) 
            for (int j = 0; j < n; j++) 
                scanf("%d", &(tims[i][j]));
        for (int i = 0; i < n; i++) 
            for (int j = 0; j < n; j++) 
                scanf("%d", &(riss[i][j]));
        
        minr = mint = 0;

        busca(0, 0, 0);
        
        if (!mint) printf("-1\n");
        else printf("%u %u\n", minr, mint);
    }
}
