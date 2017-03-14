#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 100007;
const ll MOD = 1000000007;

char c;
ll res;

int convert (char c) {
    if (c >= '0' && c <= '9')
        return c-'0';
    if (c >= 'A' && c <= 'Z')
        return c-'A'+10;
    if (c >= 'a' && c <= 'z')
        return c-'a'+36;
    if (c == '-')
        return 62;
    if (c == '_')
        return 63;
}

ll treepot (int e) {
    ll res = 1;
    while (e--)
        res = (res*3)%MOD;
    return res;
}

int main () {
    res = 1;
    while (scanf(" %c", &c) != EOF) {
        int x = convert(c);
        ll mul = (treepot(6-__builtin_popcount(x)));
        res = (res*mul)%MOD;
    }

    printf("%I64d\n", res);
}
