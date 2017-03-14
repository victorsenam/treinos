#include <bits/stdc++.h>

using namespace std;

#define MAX 1001

int aux, sum1, sum2, n;
vector<int> lista;

int main () {
    lista.reserve(MAX);

    while (scanf("%d", &n) != EOF) {
        for (int i = 0; i < n; i++) {
            scanf("%d", &(lista[i]));
        }
        sort(lista.begin(), lista.begin()+n);

        sum1 = sum2 = 0;
        lista[n] = lista[0];

        for (int i = 0; i < n/2; i++) {
            aux = lista[i*2] - lista[i*2+1];
            if (aux < 0) aux = -aux;
            if (aux > 24-aux) aux = 24-aux;

            sum1 += aux;

            aux = lista[i*2+1] - lista[i*2+2];
            if (aux < 0) aux = -aux;
            if (aux > 24-aux) aux = 24-aux;

            sum2 += aux;
        }

        if (sum1 < sum2) printf("%d\n", sum1);
        else printf("%d\n", sum2);
    }
}
