#include <bits/stdc++.h>

using namespace std;

const int Q = 15007;
const int N = 10000000;

int pri[Q];
int sieve[N];
int qtd;
int n, t;

int main () {
    scanf("%d", &t);

    qtd = 0;
    for (int i = 2; i < N; i++) {
        if (qtd >= Q)
            break;

        if (sieve[i]) {
            continue;
        }
        pri[qtd++] = i;
        
        for (int j = 1; j*i < N; j++)
            sieve[j*i] = 1;
    }

    while (t--) {
        scanf("%d", &n);
        printf("%d\n", pri[n-1]);
    }
}
