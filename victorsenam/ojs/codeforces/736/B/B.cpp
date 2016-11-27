#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define debug(...) {fprintf(stderr, __VA_ARGS__);}

map<ll, ll> memo;

bool isprime (ll n) {
    if (n < 2) return 0;
    
    for (ll i = 2; i*i <= n; i++)
        if (n%i == 0) return 0;

    return 1;
}

int main () {
    ll n;
    scanf("%lld", &n);
    if (isprime(n))
        printf("1\n");
    else if (isprime(n-2))
        printf("2\n");
    else if (n%2)
        printf("3\n");
    else
        printf("2\n");
}
