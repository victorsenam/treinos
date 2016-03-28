#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 200007;
const ll K = 1000000007ll;

ll a[N], in[N];
int n, ls;
ll k;

int main () {
    scanf("%d %I64d", &n, &k);

    for (int i = 0; i <= n; i++){
        scanf("%I64d", in+i);
        a[i] = in[i];
    }

    ls = n;
    for (int i = 0; i < n; i++) {
        if (a[i]%2 == 0) {
            a[i+1] += (a[i]/2ll);
            a[i] = 0;
        } else {
            ls = i;
            break;
        }
    }

    for (int i = n; i > ls; i--) {
        if (abs(a[i]) >= K*(10000000ll)) {
            printf("0\n");
            return 0;
        }
        a[i-1] += (a[i]*2ll);
    }
    int cnt = 0;
    for (int i = ls; i >= 0 && abs(a[i]) < K*(100000ll); i--) {
        DEBUG("%d : [%I64d]\n", i, a[i]);
        if (abs(in[i]-a[i]) <= k) {
            cnt += (i != n || in[i] != a[i]);
        } else {
            DEBUG("not %d\n", i);
        }
        a[i-!!i] = (a[i]*2ll);
    }

    printf("%d\n", cnt);
    return 0;
}
