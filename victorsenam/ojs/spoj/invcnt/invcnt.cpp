#include <cstdio>

using namespace std;

#define MAX 2000000

long long int aux[MAX+1], v[MAX+1];
int t;
unsigned long long int m, invs;

void msort (int de, int ate) {
    int i = 0;
    int meio = (de+ate)/2, cm = de, mm = meio;
    if (meio != de) {
        msort(de, meio);
        msort(meio, ate);

        while (mm < ate && cm < meio) {
            if (v[cm] > v[mm]) {
                aux[i++] = v[mm++];
                invs += (meio-cm);
  //              printf("%d > %d x %d\n", v[cm], v[mm-1], meio-cm);
            } else aux[i++] = v[cm++];
        }

        while (mm < ate) aux[i++] = v[mm++];
        while (cm < meio) aux[i++] = v[cm++];

        cm = de;
        for (int j = 0; j < i; j++) {
            v[cm++] = aux[j];
        }
    }
}

int main () {
    scanf("%d", &t);
    while (t--) {
        scanf("%llu", &m);
        
        invs = 0llu;

        for (int i = 0; i < m; i++) scanf("%lld", &(v[i]));

//        for (int i = 0; i < m; i++) printf("%d ", v[i]);
//        printf("\n");

        msort(0, m);

//        for (int i = 0; i < m; i++) printf("%d ", v[i]);
//        printf("\n");

        printf("%llu\n", invs);
    }
}
