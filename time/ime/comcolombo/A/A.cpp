#include <bits/stdc++.h>

using namespace std;

const int N = 102;

int n, a[N], p;
int maxi[N];
int res[N];
int t;
int ss;

bool cmp (int i, int j) {
    if (a[i] == a[j])
        return i < j;
    return a[i] < a[j];
}

bool solve (int k, int tot) {
    for (int i = 0; i < n; i++) {
        if (res[i] != -1)
            continue;

        if (a[i]+k < p/n)
            return 0;
        tot -= min(a[i], p/n+k);
    }

    return (tot<=0);
}


void run () {
    int tot = p;
    int kmax = p;

    for (int i = 0; i < n; i++) {
        printf("==%d\n", i);
        int lo, hi, mid;
        lo = 0;
        hi = kmax;
        mid = lo + (hi-lo)/2;
        while (lo < hi) {
            mid = lo + (hi-lo)/2;
            if (solve(mid, tot)) {
                hi = mid;
                printf("%d ==> 1\n", mid);
            } else {
                lo = mid+1;
                printf("%d ==> 0\n", mid);
            }
        }

        kmax = min(kmax, mid);
        res[maxi[n-1-i]] = min(a[maxi[n-1-i]], p/n+mid);
        tot -= res[maxi[n-1-i]];
    }
}

int main () {
    scanf("%d", &t);

    while (t--) {
        scanf("%d %d", &p, &n);
        memset(res, -1, sizeof res);

        for( int i = 0; i < n; i++) {
            scanf("%d", a+i);
            maxi[i] = i;
        }

        sort(maxi, maxi+n, cmp);
        
        ss = 0;
        run();

        for (int i = 0; i < n; i++) {
            if (i) printf(" ");
            printf("%d", res[i]);
        }
        printf("\n");
    }
}
