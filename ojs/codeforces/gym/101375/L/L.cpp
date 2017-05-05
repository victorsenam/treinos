#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define debug(...) {}
#endif

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

int n;
ll s, a, mn;

int main () {
    scanf("%d", &n);

    mn = LLONG_MAX;

    for (int i = 0; i < n; i++) {
        scanf("%lld", &a);
        if (a&1)
            mn = min(mn, a);
        s += a;
    }

    if (s&1)
        s -= mn;
    printf("%lld\n", s);
}
