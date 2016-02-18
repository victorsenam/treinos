#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef int num;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 307;

int n;
int a[N];
int pre[N], pos[N];
ll freq[N];
ll t;

int main () {
    scanf("%d %lld", &n, &t);

    for (int i = 0; i < n; i++) {
        scanf("%d", a+i);
        a[i+n+n] = a[i+n] = a[i];
        freq[a[i]]++;
    }

    for (int i = 0; i < 3*n; i++) {
        pre[i] = 1;
        for (int j = 0; j < i; j++)
            if (a[i] >= a[j])
                pre[i] = max(pre[i], pre[j]+1);
    }

    if (t <= 3) {
        int maxi = 0;
        for (int i = 0; i < t*n; i++)
            maxi = max(maxi, pre[i]);
        printf("%d\n", maxi);
        return 0;
    }

    for (int i = (n<<1)-1; i >= 0; i--) {
        pos[i] = 1;
        for (int j = i+1; j < (n<<1); j++)
            if (a[i] <= a[j])
                pos[i] = max(pos[i], pos[j]+1);
    }

    ll maxi = 0;
    for (int i = 0; i < (n<<1); i++) {
        for (int j = 0; j < (n<<1); j++) {
            for (int k = a[i]; k <= a[j]; k++) {
                ll res = (t-4)*freq[k] + pre[i] + pos[j];

                if (res > maxi) {
                    //DEBUG("%d(%d) [%d](%d*%d) %d(%d) -> %d\n", i, pre[i], k, freq[k], t-4, j, pos[j], res);
                    maxi = res;
                }
            }
        }
    }

    printf("%lld\n", maxi);
}
