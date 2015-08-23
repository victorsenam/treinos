#include <bits/stdc++.h>

using namespace std;

int n;

int main () {
    while (scanf("%d", &n) != EOF && n) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                printf("%3d", min(min(i+1, j+1), min(n-i, n-j)));
                if (j != n-1) printf(" ");
            }
            printf("\n");
        }
        printf("\n");
    }
}
