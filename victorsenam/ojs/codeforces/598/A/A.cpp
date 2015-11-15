#include <bits/stdc++.h>

int t;
long long int ans, n;

int main () {
    scanf("%d", &t);

    while (t--) {
        scanf("%I64d", &n);

        ans = n*(n+1)/2 + 2;

        int pot = 1;
        while (n) {
            n >>= 1;
            pot++;
        }

        ans -= (1ll<<pot);
        printf("%I64d\n", ans);
    }
}

