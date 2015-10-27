#include <bits/stdc++.h>

using namespace std;

const int N = 2007;

typedef long long num;

int k, n;
num pd[N];
int in;
num a[N];
num cnt;

num solve (num lim) {
    pd[n-1] = 0;
    for (int i = n-2; i >= 0; i--) {
        pd[i] = n - i - 1;
        for (int j = i+1; j < n; j++) {
            if (abs(a[j] - a[i]) > lim*(j-i))
                continue;
            pd[i] = min(pd[i], pd[j] + (j-i-1));
        }
    }
    num res = pd[0];
    for (int i = 1; i < n; i++)
        res = min(res, pd[i] + i);
    return res;
}

int main () {
    scanf("%d %d", &n, &k);

    num maxi = INT_MIN;
    num mini = INT_MAX;
    for (int i = 0; i < n; i++) {
        scanf("%d", &in);
        a[i] = in;
        maxi = max(maxi, a[i]);
        mini = min(mini, a[i]);
    }

    num lo = 0;
    num hi = maxi-mini;

    cnt = 0;
    while ( lo < hi ) {
        num lim = lo + (hi-lo)/2;
        
        if (solve(lim) > k)
            lo = lim+1;
        else
            hi = lim;
    }
    printf("%d\n", (int) lo);
}
