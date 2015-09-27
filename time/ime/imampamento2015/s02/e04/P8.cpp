#include <bits/stdc++.h>


using namespace std;

int a, b, d;
int n, k;

int main () {
    scanf("%d %d", &n, &k);

    d = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &a, &b);
        d += b - a + 1;
    }
    d %= k;

    printf("%d\n", (k - d)%k);
}
