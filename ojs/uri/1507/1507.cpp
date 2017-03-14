#include <cstdio>
#include <algorithm>

struct ordenado {
    char letra;
    int  pos;
} mapa[100000];

bool searchCond (ordenado item, char val) {
    return item.letra < val;
}

int main () {
    int     N, Q, i, j, ant;
    char    subseq[100], atual;

    scanf("%d ", &N);

    while ( N > 0 ) {
        scanf("%c", &atual);
        for (i = 0; atual != '\0'; i++) {
            mapa[i].letra = atual;
            for (j = i; j > 0 && mapa[j].letra < mapa[j-1].letra; j--) {
                atual = mapa[j-1].letra;
                mapa[j-1].letra = mapa[j].letra;
                mapa[j].letra = atual;
            }
            scanf("%c", &atual);
        }

        scanf("%d", &Q);

        while ( Q > 0 ) {
            scanf("%s", subseq);
            
            ant = 0;
            for (i = 0; subseq[i] != '\0'; i++) {
                j = std::lower_bound(mapa, mapa+100000, subseq[i], searchCond);

                while ( mapa[j].letra == subseq[i] ) {
                    if ( mapa[j].pos > ant ) break;
                    j++;
                }
                if ( mapa[j].letra != subseq[i] ) break;
            }
            if ( subseq[i] == '\0' ) printf("Yes\n");
            else printf("No\n");

            Q--;
        }


        N--;
    }
        
}
