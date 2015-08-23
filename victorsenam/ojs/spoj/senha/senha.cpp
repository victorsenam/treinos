#include <bits/stdc++.h>

char assoc[5], senha[6];
int n, a, b, t;
char aux;

int main () {
    t = 0;
    while (scanf("%d", &n) != EOF && n) {
        t++;
        for (int i = 0; i < 5; i++) {
            scanf("%d %d", &a, &b);
            assoc[i] = 10*a + b;
        }

        for (int i = 0; i < 6; i++) {
            scanf(" %c", &aux);
            senha[i] = assoc[aux - 'A'];
        }

        for (int j = 1; j < n; j++) {
            for (int i = 0; i < 5; i++) {
                scanf("%d %d", &a, &b);
                assoc[i] = 10*a + b;
            }

            for (int i = 0; i < 6; i++) {
                scanf(" %c", &aux);
                
                a = assoc[aux - 'A']/10;
                b = assoc[aux - 'A']%10;

                if (a == senha[i]/10 && b != senha[i]%10) senha[i] = a;
                else if (b == senha[i]/10 && a != senha[i]%10) senha[i] = b;
                else if (a == senha[i]%10 && b != senha[i]/10) senha[i] = a;
                else if (b == senha[i]%10 && a != senha[i]/10) senha[i] = b;
            }
        }

        printf("Teste %d\n", t);
        for (int i = 0; i < 6; i++) {
            printf("%d", senha[i]);
            if (i < 5) printf(" ");
        }
        printf("\n\n");
    }
}
