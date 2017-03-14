#include <bits/stdc++.h>

int n, i;

int main () {
    i = 1;
    while (scanf("%d", &n) != EOF && n) {
        printf("Teste %d\n", i++);
        printf("%d\n\n", (1<<n)-1);
    }
}
