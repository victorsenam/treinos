#include <bits/stdc++.h>

int main () {
    printf("1000 1000\n");
    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < 1000; j++) {
            printf("%d ", (i+j)%2);
        }
        printf("\n");
    }
}
