#include <cstdio>

int t = 1, d;

int main () {
    while (scanf("%d", &d) != EOF && d) {
        printf("Teste %d\n", t++);
        
        printf("%d ", d/50);
        d %= 50;

        printf("%d ", d/10);
        d %= 10;

        printf("%d ", d/5);
        d %= 5;

        printf("%d\n\n", d);
    }
}
