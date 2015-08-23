#include <bits/stdc++.h>

using namespace std;
typedef int num;
#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#else
#define debug(...) //
#endif

#define N 100000

int seg[4*N+1];
int t, q, n, a, b, c;

void setEl(int dest, int val, int root, int lo, int hi) {
    if (lo + 1 >= hi)
        seg[root] = val;
    else {
        int mid = lo+(hi-lo)/2;
        if (dest < mid)
            setEl(dest, val, 2*root, lo, mid);
        else
            setEl(dest, val, 2*root+1, mid, hi);

        seg[root] = min(seg[2*root], seg[2*root+1]);
    }
}

int getInt(int root, int l, int r, int lo, int hi) {
    if (lo >= l && hi <= r) {
        debug("%d", root);
        return seg[root];
    }
    if (lo >= r || hi <= l) return INT_MAX;

    int mid = lo+(hi-lo)/2;
    return min(getInt(root*2, l, r, lo, mid), getInt(root*2+1, l, r, mid, hi));
}

int main () {
    scanf("%d", &t);
    c = 1;

    while (t--) {
        scanf("%d %d", &n, &q);

        for (int i = 0; i < n; i++) {
            scanf("%d", &a);
            setEl(i, a, 1, 0, n);
 //           for (int j = 1; j <= 4*n; j++)
 //               printf("%d ", seg[j]);
 //           printf("\n");
        }

        printf("Scenario #%d:\n", c++);
        for (int i = 0; i < q; i++) {
            scanf("%d %d", &a, &b);
            printf("%d\n", getInt(1, a-1, b, 0, n));
        }
    }
}
