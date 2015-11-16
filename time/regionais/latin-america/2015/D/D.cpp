#include <bits/stdc++.h>

using namespace std;

typedef long long int num;

const int N = 23;
const int M = 53;

num need[M];
num has[M];
int n, m;

int main () {
    while (scanf("%d %d", &n, &m) != EOF) {
        num def = 0;
        num res = 0;
        for (int i = 0; i < m; i++) {
            scanf("%lld", need+i);
            scanf("%lld", has+i);
            num a;

            for (int j = 1; j < n; j++) {
                scanf("%lld", &a);
                need[i] -= a;
            }

            if (need[i] >= has[i])
                def += has[i];
            num pot = 1;
            for (pot = 1; pot <= need[i] && pot <= 10000; pot *= 10);
            res += pot/10;

        }

        printf("%lld\n", res - def);
    }
}
