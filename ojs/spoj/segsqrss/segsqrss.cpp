#include <bits/stdc++.h>

using namespace std;
typedef long long int num;
#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#else
#define debug(...) //
#endif

#define N 100000
#define MAX 4*N+1

struct seg {
    int esq[MAX], dir[MAX];
    num sum[MAX], comb[MAX], lazyAdd[MAX], lazySet[MAX];
    bool toSet[MAX];
    num vals[N];

    void inputVals (int n) {
        for (int i = 0; i < n; i++)
            scanf("%lld", &vals[i]);
    }

    void build (int root, int e, int d) {
        esq[root] = e;
        dir[root] = d;
        lazyAdd[root] = 0;
        toSet[root] = 0;
        if (d - e == 1) {
            sum[root] = vals[e];
            comb[root] = 0;
            debug("%d[%d,%d) -> sum %lld comb %lld val %lld", root, esq[root], dir[root], sum[root], comb[root], sum[root]*sum[root]-2*comb[root]);
            return;
        }

        build(2*root, e+(d-e)/2, d);
        build(2*root+1, e, e+(d-e)/2);
        sum[root] = sum[2*root] + sum[2*root+1];
        comb[root] = comb[2*root] + comb[2*root+1] + sum[2*root]*sum[2*root+1];
        debug("%d[%d,%d) -> sum %lld comb %lld val %lld", root, esq[root], dir[root], sum[root], comb[root], sum[root]*sum[root]-2*comb[root]);
    }

    void refresh (int root) {
        if (toSet[root]) {
            sum[root] = (dir[root]-esq[root])*lazySet[root];
            comb[root] = (dir[root]-esq[root]-1)*lazySet[root]*lazySet[root];
            toSet[root] = 0;
            if (dir[root] - esq[root] > 1) {
                toSet[2*root] = toSet[2*root+1] = 1;
                lazySet[2*root] = lazySet[2*root+1] = lazySet[root];
                lazyAdd[2*root] = lazyAdd[2*root+1] = 0;
            }
        }
    
        comb[root] += lazyAdd[root]*(dir[root]-esq[root]-1)*sum[root] + (dir[root]-esq[root]-1)*(dir[root]-esq[root])*lazyAdd[root]*lazyAdd[root]/2;
        sum[root] += (dir[root]-esq[root])*lazyAdd[root];
        if (dir[root] - esq[root] > 1) {
            lazyAdd[2*root] += lazyAdd[root];
            lazyAdd[2*root+1] += lazyAdd[root];
        }
        lazyAdd[root] = 0;
    }

    void add (int root, int e, int d, num x) {
        refresh(root);
        debug("[%d,%d) add %lld : [%d,%d)", e, d, x, esq[root], dir[root]);
        if (esq[root] >= e && dir[root] <= d) {
            lazyAdd[root] += x;
            refresh(root);
            debug("[%d,%d) added %lld to [%d,%d) -> sum %d comb %d val %d", e, d, x, esq[root], dir[root], sum[root], comb[root], sum[root]*sum[root]-2*comb[root]);
            return;
        }
        if (esq[root] >= d || dir[root] <= e)
            return;
        
        add(2*root, e, d, x);
        add(2*root+1, e, d, x);

        sum[root] = sum[2*root] + sum[2*root+1];
        comb[root] = comb[2*root] + comb[2*root+1] + sum[2*root]*sum[2*root+1];
    }

    void set (int root, int e, int d, num x) {
        refresh(root);
        if (esq[root] >= e && dir[root] <= d) {
            lazySet[root] = x;
            lazyAdd[root] = 0;
            toSet[root] = 1;
            refresh(root);
            return;
        }
        if (esq[root] >= d || dir[root] <= e)
            return;

        set(2*root, e, d, x);
        set(2*root+1, e, d, x);
        
        sum[root] = sum[2*root] + sum[2*root+1];
        comb[root] = comb[2*root] + comb[2*root+1] + sum[2*root]*sum[2*root+1];
    }
    
    pair<num, num> getVal (int root, int e, int d) {
        refresh(root);
        if (esq[root] >= e && dir[root] <= d)
            return make_pair(sum[root], comb[root]);
        if (esq[root] >= d || dir[root] <= e)
            return make_pair(0, 0);

        pair<int, int> a, b;
        a = getVal(2*root, e, d);
        b = getVal(2*root+1, e, d);

        return make_pair(
            a.first + b.first,
            a.second + b.second + a.first*b.first
        );
    }
};

int n, k, a, b, t, c, q;
num x;
seg tree;
pair<num, num> res;

int main () {
    scanf("%d", &t);
    for (int c = 1; c <= t; c++) {
        printf("Case %d:\n", c);
        scanf("%d %d", &n, &q);
        tree.inputVals(n);
        tree.build(1, 0, n);
        for (int i = 0; i < q; i++) {
            scanf("%d %d %d", &k, &a, &b);
            if (k == 2) {
                res = tree.getVal(1, a-1, b);
                printf("%lld\n", res.first*res.first-2*res.second);
                continue;
            }
            scanf("%lld", &x);
            if (k == 1)
                tree.add(1, a-1, b, x);
            else 
                tree.set(1, a-1, b, x);
        }
    }
}
