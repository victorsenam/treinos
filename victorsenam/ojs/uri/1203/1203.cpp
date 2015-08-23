#include <cstdio>
#include <algorithm>

bool buscasoma(int * vet, int i, int parc, int obj, int R) {
    if (i > R || !vet[i]) return 0;
    parc += vet[i];
    if (parc == obj) return 1;
    if (parc > obj) return buscasoma(vet, i+1, parc-vet[i], obj, R);
    if (buscasoma(vet, i+1, parc, obj, R)) return 1;
    return buscasoma(vet, i+1, parc-vet[i], obj, R);
}

bool sorter (int i,int j) { return (i>j); }

int main () {
    int R, K, i, sum[100], aux;

    while (scanf("%d %d", &R, &K) != EOF) {
        for (i = 0; i < R; i++) {
            sum[i] = 0;
        }
        for (i = 0; i < K; i++) {
            scanf("%d", &aux);
            sum[aux-1]++;
            scanf("%d", &aux);
            sum[aux-1]++;
        }
        std::sort(sum, sum+R, sorter); // sort em ordem crescente
        if (buscasoma(sum, 0, 0, K, R)) printf("S\n");
        else printf("N\n");
    }
}
