#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 1e4+7;

int fr[N];
ll a;
int n;

int main () {
    n = 10;

    for (int i = 0; i < n; i++) {
        scanf("%d", &a);

        for (ll j = 2; j*j <= a; j++)
            while (a%j == 0) {
                fr[j]++;
                a /= j;
            }
        fr[a]++;
    }

    ll res = 1;
    for (int i = 2; i < N; i++)
        res = (res*(fr[i]+1))%10;
    printf("%lld\n", res);
}
