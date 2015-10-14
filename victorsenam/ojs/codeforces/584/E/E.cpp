#include <bits/stdc++.h>

using namespace std;;

const int N = 1000000000;
const int SN = 4000000;

bool sieve[SN];
int n;
int i;

bool isPrime (int v) {
    if (v*v < SN)
        return (!sieve[v]);
    for (int i = 2; i*i <= v; i++) {
        if (sieve[i])
            continue;
        if (v%i == 0)
            return 0;
    }
    return 1;
}

int main () {
    scanf("%d", &n);
    for (int i = 2; i < SN; i++) {
        if (sieve[i])
            continue;
        for (int j = 2; j*i < SN; j++)
            sieve[j*i] = 1;
    }

    if (isPrime(n))
        printf("1\n%d\n", n);
    else {
        printf("3\n");
        for (int i = 2; i < n && n-2*i >= 0; i++) {
            if (i < n-2*i) {
                if (!isPrime(i))
                    continue;
                if (!isPrime(n-2*i))
                    continue;

                printf("%d %d %d\n", i, i, n-2*i);
                break;
            } else {
                if (!isPrime(n-2*i))
                    continue;
                if (!isPrime(i));
                    continue;

                printf("%d %d %d\n", i, i, n-2*i);
                break;
            }
        }
    }
}
