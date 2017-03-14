#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

ll n, k;

int main () {
    scanf("%lld %lld", &n, &k);
    ll res = n;
    while (n >= k) {
        res += n/k;
        n = n - (k-1)*(n/k);
    }

    printf("%lld\n", res);
}
