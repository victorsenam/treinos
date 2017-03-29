#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 1e5+7;

int n;
ll a[N];
vector<int> nx[N];
int pr[N];

int pd[N];

int main () {
    scanf("%d", &n);

    for (int i = 0; i < N; i++)
        pr[i] = n;

    for (int i = 0; i < n; i++)
        scanf("%lld", &a[i]);

    a[n] = -1;
    pd[n] = 0;
    int res = 0;
    for (int i = n-1; i >= 0; i--) {
        ll x = a[i];

        nx[i].push_back(n);
        for (ll j = 2; j*j <= x; j++) {
            if (x%j == 0) {
                nx[i].push_back(pr[j]);
                pr[j] = i;
            }
            while (x%j == 0)
                x /= j;
        }

        if (x > 1) {
            nx[i].push_back(pr[x]);
            pr[x] = i;
        }

        pd[i] = 0;
        for (int j : nx[i]) {
            pd[i] = max(pd[i], pd[j] + 1);
        }
        res = max(res, pd[i]);
    }

    printf("%d\n", res);
}
