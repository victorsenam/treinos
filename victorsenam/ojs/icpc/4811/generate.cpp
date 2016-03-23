#include <bits/stdc++.h>

using namespace std;

int main () {
    int n = 10000;

    printf("%d\n", n);
    for (int i = 0; i < 10; i++) {
        for (int j = 1; j <= 1000; j++) {
            for (int k = 0; k < j; k++)
                putchar('a'+i);
            putchar('\n');
        }
    }
    printf("0\n");
}
