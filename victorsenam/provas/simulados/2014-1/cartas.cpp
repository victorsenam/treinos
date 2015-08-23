#include <stdio.h>

void trocar(char * vetor, int n, int m) {
    char    aux_n,        // auxiliar
            aux_m,        // auxiliar
            mask = 15;    // mascara 00001111

    aux_n = vetor[n/2];
    aux_m = vetor[m/2];

    if (n%2) {
        aux_n &= mask;
        vetor[n/2] &= ~mask;
    } else {
        aux_n &= ~mask;
        vetor[n/2] &= mask;
    }

    if (m%2) {
        aux_m &= mask;
        vetor[m/2] &= ~mask;
    } else {
        aux_m &= ~mask;
        vetor[m/2] &= mask;
    }
    
    if (n%2 != m%2) {
        if (aux_n < aux_m) {
            aux_n <<= 4;
            aux_m >>= 4;
        } else {
            aux_n >>= 4;
            aux_m <<= 4;
        }
    }

    vetor[n/2] |= aux_m;
    vetor[m/2] |= aux_n;
}

int main () {
    static char    cartas[50000][26]; // 1 char = 1 byte = 8 bits = 2 cartas = 1/26 baralho
           char    comm;             // comando
           int     N,                // baralhos
                   M,                // movimentos
                   A, B, I, J,       // info
                   i, j,             // interadores
                   sum;

    while( scanf("%d %d", &N, &M) != EOF ) {
        // inicalizando vetor
        for (i = 0; i < 26; i++) {
            cartas[0][i] = (char) ( ((i*2)%13 + 1) << 4 ) + ( ((i*2+1)%13 + 1) );
        }
        
        for (i = 1; i < N; i++) {
            for (j = 0; j < 26; j++) {
                cartas[i][j] = cartas[0][j];
            }
        }
        
        while (M > 0) {
            scanf(" %c ", &comm);
            
            // pega comando
            if ( comm == 'E' ) {
                scanf(" %d %d %d %d ", &A, &B, &I, &J);
                
                // embaralhando
                for (i = A; i < B; i++) {
                    trocar(cartas[i], I, J);            
                }
            } else {
                scanf("%d %d", &A, &B);

                sum = 0;

                for (i = A; i < B; i++) {
                    sum += (int) (cartas[i][25] & 15);
                }
                
                printf("%d\n", sum);
            }

            M--;
        }
    }
}
