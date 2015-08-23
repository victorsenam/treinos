#include <bits/stdc++.h>

using namespace std;

int n, i;

int main () {
    scanf("%d", &n);

    if (n < 4) {
        printf("NO\n");
        return 0;
    }

    printf("YES\n");
    
    if (n%4 == 0) {
        printf("3 * 4 = 12\n");
        printf("2 * 1 = 2\n");
        printf("12 * 2 = 24\n");
    } else if (n%4 == 1) {
        printf("2 - 1 = 1\n");
        printf("5 * 4 = 20\n");
        printf("20 + 1 = 21\n");
        printf("21 + 3 = 24\n");
    } else if (n%4 == 2) {
        printf("5 * 6 = 30\n");
        printf("30 - 1 = 29\n");
        printf("29 + 2 = 31\n");
        printf("31 - 3 = 28\n");
        printf("28 - 4 = 24\n");
    } else {
        printf("5 * 6 = 30\n");
        printf("4 * 3 = 12\n");
        printf("30 - 12 = 18\n");
        printf("18 + 7 = 25\n");
        printf("25 - 2 = 23\n");
        printf("23 + 1 = 24\n");
    }
    
    i = 5 + n%4;
    while (i < n) {
        printf("%d - %d = 1\n", i+1, i);
        printf("%d - %d = 1\n", i+3, i+2);
        printf("1 - 1 = 0\n");
        printf("24 + 0 = 24\n");
        i += 4;
    }
}
