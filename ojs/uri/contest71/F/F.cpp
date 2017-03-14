#include <bits/stdc++.h>

using namespace std;

const int N = 1000007;

typedef long long int num;

bool sieve[N];
bool gem[N];
int acc[N];
int n;
int x, y;

int main () {
    sieve[0] = sieve[1] = 1;
    for (num i = 2; i < N; i++) {
        if (sieve[i])
            continue;
        for (num j = 2; j*i < N; j++)
            sieve[i*j] = 1;
    }

    for (int i = 2; i < N; i++) {
        if (!sieve[i] && (!sieve[i-2] || !sieve[i+2])) {
            gem[i] = 1;
        }
    }

    acc[0] = 0;
    for (int i = 0; i < N; i++)
        acc[i] = acc[i - (i>0)] + gem[i];

    scanf("%d", &n);

    while (n--) {
        scanf("%d %d", &x, &y);
        if (x > y)
            swap(x, y);
        printf("%d\n", acc[y]-acc[x-1]);
    }
}
