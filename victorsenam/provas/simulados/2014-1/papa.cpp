/* H: Trabalho do Papa. ~le Problema do Papa */
#include <stdio.h>

#define LIM 1000

struct box {
    int P;      // Peso
    int R;      // Resistência
};

/* Variáveis Globais */
struct box      caixas[LIM]; // Vetor de Caixas
int             ordem[LIM];  // Ordem das Caixas por Peso Crescente

// Função para montar pilha
// base : resistencia da pilha abaixo
// k : quantidade de caixas já empilhadas
// n : quantidade de caixas disponíveis
// u : ultimo item colocado na pilha
int mount (int base, int k, int n, int s) {
    int     res,    // resistencia atual
            m = k,  // maior pilha
            t,      // pilha atual
            i;

    if ( base == 0 ) return k+1;
    else if ( base < 0 ) return k;

    for (i = s+1; i < n; i++) {
        res = base;
        if ( res > caixas[ordem[i]].R ) res = caixas[ordem[i]].R;
        
        res -= caixas[ordem[i]].P;

        t = mount(res, k+1, n, i);
        if (t > m) m = t;
    }
    
    return m;
}

int main () {
    int     T,  // instancias
            n,  // qtd. caixas
            i,
            j,
            aux,
            stack[LIM],
            R;

    scanf("%d", &T);

    while (T > 0) {
        scanf("%d", &n);

        for (i = 0; i < n; i++) {
            scanf("%d %d", &(caixas[i].P), &(caixas[i].R));

            for (j = i; j > 0; j--) {
                if (caixas[i].P > caixas[i-1].P) {
                    aux = caixas[i].P;
                    caixas[i].P = caixas[i-1].P;
                    caixas[i-1].P = aux;
                    aux = caixas[i].R;
                    caixas[i].R = caixas[i-1].R;
                    caixas[i-1].R = aux;
                } else break;
            }
        }

        printf("%d", mount(1000000, 0, n, -1));

        T--;
    }
}
