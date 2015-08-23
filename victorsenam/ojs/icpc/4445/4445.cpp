#include <bits/stdc++.h>

using namespace std;

const int N = 10;

pair<int, int> v[N];
int lo, hi, mid;
int n, t;

bool solve (int k) {
    sort(v, v+n);
    bool ok = 0;
    int last;
    do {
        last = 0;
        for (int i = 0; i < n; i++) {
            if (v[i].second < last)
                break;
            else if (i == n-1)
                ok = 1;
            last = max(last, v[i].first) + k;
        }
    } while (next_permutation(v, v+n) && !ok);
    return ok;
}

int main () {
    int c = 1;
    while (scanf("%d", &n) != EOF && n) {
        for (int i = 0; i < n; i++) {
            scanf("%d %d", &v[i].first, &v[i].second);
            v[i].first *= 60*100;
            v[i].second *= 60*100;
        }
        lo = 1;
        hi = 1440*60*100;
        mid = (hi+lo+1)/2;
        while (lo < hi) {
            if (solve(mid))
                lo = mid;
            else
                hi = mid-1;
            mid = (hi+lo+1)/2;
        }
        if (mid % 100 >= 50) {
            mid /= 100;
            mid++;
        } else
            mid /= 100;
        printf("Case %d: %d:%02d\n", c++, mid/60, mid%60);
    }
}
