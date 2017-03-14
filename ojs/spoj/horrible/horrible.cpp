#include <bits/stdc++.h>

using namespace std;
typedef int num;
#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#else
#define debug(...) //
#endif

#define N 100000
#define MAX N*4+1

struct seg {
    int esq[MAX], dir[MAX];
    long long int sum[MAX], lazy[MAX];

    void build (int root, int e, int d) {
        esq[root] = e;
        dir[root] = d;
        
        sum[root] = lazy[root] = 0;

        if (e + 1 >= d) return;
        build(root*2, e, (e+d)/2);
        build(root*2+1, (e+d)/2, d);
    }

    void update (int root, int e, int d, int v) {
        refresh(root);
        if (e <= esq[root] && d >= dir[root]) {
            lazy[root] = v;
            refresh(root);
            return;
        }
        if (e >= dir[root] || d <= esq[root])
            return;

        update(2*root, e, d, v);
        update(2*root+1, e, d, v);
        sum[root] = sum[2*root] + sum[2*root+1];

    }

    int getVal (int root, int e, int d) {
        refresh(root);
        if (e <= esq[root] && d >= dir[root]) return sum[root];
        if (e >= dir[root] || d <= esq[root]) return 0;
        return getVal(2*root, e, d) + getVal(2*root+1, e, d);
    }

    void refresh (int root) {
        sum[root] += lazy[root]*(dir[root]-esq[root]);
        if (dir[root] - esq[root] > 1) {
            lazy[2*root] += lazy[root];
            lazy[2*root+1] += lazy[root];
        }
        lazy[root] = 0;
    }
};

int t, n, q, a, b, k;
long long v;
seg tree;

int main () {
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &n, &q);
        tree.build(1, 0, n);

        while (q--) {
            scanf("%d %d %d", &k, &a, &b);
            a--;
            if (k == 0) {
                scanf("%lld", &v);
                tree.update(1, a, b, v);
            } else
                printf("%d\n", tree.getVal(1, a, b));
        }
    }
}
