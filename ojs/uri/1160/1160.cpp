#include <cstdio>

int main () {
    int     PA, PB, GA, GB, T, anos, aux;

    scanf("%d", &T);

    while ( T > 0 ) {
        anos = 0;

        scanf("%d %d %d.%d", &PA, &PB, &GA, &aux);
        GA = 10*GA + aux;

        scanf("%d.%d", &GB, &aux);
        GB = 10*GB + aux;

        PA *= 10;
        PB *= 10;

        while ( PA <= PB && anos <= 100 ) {
            // cresce
            PA += PA * GA / 1000;
            PA = (PA / 10) * 10;
            PB += PB * GB / 1000;
            PB = (PB / 10) * 10;
            anos++;
        }

        if (anos > 100) {
            printf("Mais de 1 seculo.\n", anos);
        } else {
            printf("%d anos.\n", anos);
        }

        T--;
    }
}

