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

const int N = 1e5+7;

int n, k;
ll a[N];

int main () {
    scanf("%d %d", &n, &k);


    ll mn = 1e9+7;
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);

        mn = min(a[i], mn);
    }


    ll res = 0;
    for (int i = 0; i < n; i++) {
        if (a[i]%k != mn%k) {
            printf("-1\n");
            return 0;
        }

        res += (a[i] - mn)/k;
    }

    printf("%lld\n", res);
}
