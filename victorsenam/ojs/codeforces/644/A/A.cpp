#include <bits/stdc++.h>

using namespace std;

int n, a, b;

int main () {
    scanf("%d %d %d", &n, &a, &b);

    if (n > a*b) {
        printf("-1\n");
    } else {
        int p = 1;
        int q = 2;
        for (int i = 0; i < a; i++) {
            for (int j = 0; j < b; j++) {
                int r = 0;
                if (((i+j)&1) == ((a*b-1)&1)) {
                    r = p;
                    p += 2;
                } else {
                    r = q;
                    q += 2;
                }
                if (r > n)
                    r = 0;
                printf("%d ", r);
            }
            printf("\n");
        }
    }
}
