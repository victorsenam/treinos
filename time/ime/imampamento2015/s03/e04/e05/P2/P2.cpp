#include <bits/stdc++.h>

using namespace std;

const int N = 10008;
const int MAX = 10000000;
const int MIN = 0;

int v[N], hi, lo, cnt, mid, a, k, n;
int t;

bool solve(int val) {
    cnt = 0;
    for (int i = 0; i < n && cnt < k; i++) {
        cnt += v[i]/val;
    }
    if (cnt >= k)
        return 1;
    return 0;
}

int main () { 
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &n, &k);

        for (int i = 0; i < n; i++) {
            int a, b;
            scanf("%d.%d", &a, &b);
            v[i] = 100*a + b;
        }
        hi = MAX;
        lo = MIN;
        mid = (hi+lo+1)/2;

        while (lo < hi) {
            if (solve(mid))
                lo = mid;
            else
                hi = mid-1;
            mid = (hi+lo+1)/2;
        }

        printf("%d.%02d\n", mid/100, mid%100);
        if (t) printf("\n");
    }
}
