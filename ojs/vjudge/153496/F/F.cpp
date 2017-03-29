#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 2e4+7;
int t, n, k;
ll a[N];

int main () {
    scanf("%d", &t);

    while (t--) {
        scanf("%d %d", &n, &k);

        for (int i = 0; i < n; i++) {
            scanf("%lld", &a[i]);
        }
        sort(a, a+n);

        ll res = a[n-1] - a[0];
        for (int i = 0; i + k - 1 < n; i++) {
            res = min(res, a[i+k-1] - a[i]);
        }

        printf("%lld\n", res);
    }
}
