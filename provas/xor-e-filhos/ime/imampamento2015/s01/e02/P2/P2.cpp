#include <bits/stdc++.h>

int t, a[3];

int main () {
    scanf("%d", &t);
    
    for (int c = 1; c <= t; c++) {
        scanf("%d %d %d", a, a+1, a+2);
        printf("Case %d: ", c);

        if (a[0] > 20 || a[1] > 20 || a[2] > 20) {
            printf("bad\n");
        } else {
            printf("good\n");
        }
    }
}
