#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 1e5+7;
ll m, n;
ll a[N];
ll b[N];

int main () {
    scanf("%lld %lld", &m, &n);
    for (int i = 0; i < n; i++)
        scanf("%lld", &a[i]);

    sort(a, a+n);

    if (n >= m) {
        int q = n/m;
        int qt = 0;

        for (int i = 0; i < n;) {
            int j = i;
            while (j < n && a[j] == a[i]) j++;

            if (j-i == q+1) {
                b[qt++] = a[i];
            } else if (j-i != q) {
                printf("-1\n");
                return 0;
            }
            i = j;
        }

        if (qt != n%m) {
            printf("-1\n");
            return 0;
        }
        n = qt;
        for (int i = 0; i < n; i++)
            a[i] = b[i];
    }

    if (n == 0) {
        printf("1 1\n");
        return 0;
    } else if (n == 1) {
        printf("%lld 1\n", a[0]);
        return 0;
    }

    ll d = (a[0] - a[n-1] + m)%m;
    for (int i = 1; i < n; i++)
        d = max(a[i] - a[i-1], d);
    ll x = a[0];

    while (binary_search(a, a+n, (x-d+m)%m))
        x = (x-d+m)%m;

    for (ll cr = x, i = 0; i < n; i++, cr = (cr+d)%m)
        if (!binary_search(a, a+n, cr)) {
            printf("-1\n");
            return 0;
        }

    printf("%lld %lld\n", x, d);
}
