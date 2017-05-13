#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define debug(...) {}
#endif

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

int a, b, c;

int n;
ll x;

int main () {
    scanf("%d %d %d", &a, &b, &c);

    ll rs = 0;
    scanf("%d", &n);
    for (int i = 0; i < n;i++) {
        scanf("%lld", &x);

        if (x > b && x < c)
            rs++;
    }
    printf("%d\n", rs);
}
