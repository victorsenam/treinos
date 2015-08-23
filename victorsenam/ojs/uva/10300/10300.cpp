#include <bits/stdc++.h>

using namespace std;

int t, n, sum, a, b, c;

int main () {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        sum = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d %d %d", &a, &b, &c);
            sum += a*c;
        }
        printf("%d\n", sum);
    }
}
