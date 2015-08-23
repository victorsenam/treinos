#include <stdio.h>

int i;

int main () {
    printf("10000");
    for (i = 0; i < 10000; i++) {
        printf("%d %d\n", i, i+1);
    }
}
