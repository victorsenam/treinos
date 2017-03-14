#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 1e3+7;

double p[2][N];
ll k, q, qr[N];
ll rs[N];

int main () {
    scanf("%lld %lld", &k, &q);

    p[0][0] = 2000.;

    ll curr = 1;

    for (int d = 1; curr <= 1000; d++) {
        bool t = (d&1);
        p[t][0] = 0;
        for (ll i = 1; i <= k; i++)
            p[t][i] = double(p[!t][i] * i + p[!t][i-1] * (k - i + 1))/double(k);

        while (curr <= 1000 && curr < p[t][k]) {
            rs[curr] = d;
            curr++;
        }
    }

    while (q--) {
        int a;
        scanf("%d", &a);

        printf("%lld\n", rs[a]);
    }
}
