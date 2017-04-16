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

const int N = 53;

int ts;
int n, p;
ll r[N];
ll q[N][N];
int s[N];
ll a[N];

int main () {
    scanf("%d", &ts);

    for (int tt = 1; tt <= ts; tt++) {
        printf("Case #%d: ", tt);
        scanf("%d %d", &n, &p);

        for (int i = 0; i < n; i++)
            scanf("%lld", &r[i]);

        for (int i = 0; i < n; i++){
            for (int j = 0; j < p; j++)
                scanf("%lld", &q[i][j]);
            sort(q[i], q[i]+p);
            s[i] = 0;
            a[i] = 0;
        }

        int res = 0;
        bool ok = 1;
        for (ll k = 1; k <= 1e6 && ok; k++) {
            int i = 0;
            for (i = 0; i < n; i++) {
                while (s[i] < p && k*r[i]*90ll > 100ll*q[i][s[i]]) {
                    s[i]++;
                }
                if (s[i] == p) {
                    ok = 0;
                    break;
                }
                if (k*r[i]*110ll < 100ll*q[i][s[i]])
                    break;
            }

            if (i == n && ok) {
                for (int i = 0; i < n; i++) {
                    s[i]++;
                }
                res++;
                k--;
            }
        }

        printf("%d\n", res);
    }
}
