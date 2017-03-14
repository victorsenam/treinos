#include <bits/stdc++.h>

using namespace std;
typedef int num;
#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#else
#define debug(...) //
#endif


#define N 30000
#define M 1000000009
#define MAX N*4+1

struct seg {
    int fibVal[N];
    int fib[MAX];
    int vals[MAX];
    int esq[MAX], dir[MAX];
    long long int sum[MAX];
    vector<int> lazy[MAX];

    void preProcess(int n) {
        fibVal[0] = fibVal[1] = 1;
        for (int i = 0; i < n; i++) {
            scanf("%d", &vals[i]);
            if (i > 1) fibVal[i] = (fibVal[i-1] + fibVal[i-2])%M;
            debug("fib %d = %d", i, fibVal[i]);
        }
    }

    void build(int root, int e, int d) {
        if (d - e < 1) return;
        esq[root] = e;
        dir[root] = d;

        debug("%d -> [%d,%d)", root, e, d);
        lazy[root].clear();

        if (d - e == 1) {
            sum[root] = vals[e];
            debug("%d[%d,%d) get fib(%d) = %d", root, e, d, e, fibVal[e]);
            fib[root] = fibVal[e];
            return;
        }

        build(2*root, e, (e+d)/2);
        build(2*root+1, (e+d)/2, d);
        fib[root] = (fib[2*root] + fib[2*root+1])%M;
        debug("%d[%d,%d) get fib = %d", root, e, d, fib[root]);
        sum[root] = (sum[2*root] + sum[2*root+1])%M;
    }

    void add(int root, int e, int d) {
        refresh(root);
        debug("fib(%d) = %d", root, fib[root]);
        if (e <= esq[root] && d >= dir[root]) {
            lazy[root].push_back(e);
            refresh(root);
            return;
        }

        if (e >= dir[root] || d <= esq[root]) {
            return;
        }

        add(2*root, e, d);
        add(2*root+1, e, d);
        sum[root] = (sum[2*root] + sum[2*root+1])%M;
    }

    int getFib(int root, int e, int d) {
        if (e <= esq[root] && d >= dir[root])
            return fib[root];
        if (e >= dir[root] || d <= esq[root])
            return 0;

        return (getFib(2*root, e, d) + getFib(2*root+1, e, d))%M;
    }

    int getVal(int root, int e, int d) {
        refresh(root);
        debug("[%d,%d) entered %d[%d,%d)", e, d, root, esq[root], dir[root]);
        if (e <= esq[root] && d >= dir[root]) {
            debug("[%d,%d) -> %d[%d,%d) = %d", e, d, root, esq[root], dir[root], sum[root]);
            return sum[root];
        }
        if (e >= dir[root] || d <= esq[root])
            return 0;

        return (getVal(2*root, e, d) + getVal(2*root+1, e, d))%M;
    }

    void refresh(int root) {
        for (int i = 0; i < lazy[root].size(); i++) {
            sum[root] += getFib(1, esq[root] - lazy[root][i], dir[root] - lazy[root][i]);
            sum[root] %= M;

            if (dir[root] - esq[root] > 1) {
                lazy[2*root].push_back(lazy[root][i]);
                lazy[2*root+1].push_back(lazy[root][i]);
            }
        }

        lazy[root].clear();
    }

    void print(int root) {
        if (dir[root] - esq[root] < 1) return;
        print(2*root);
        print(2*root+1);
    }
};

int n, w, a, b, k, m;
seg tree;

int main () {
    scanf("%d %d", &n, &m);

    tree.preProcess(n);
    tree.build(1, 0, n);

    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &k, &a, &b);
        if (k == 1) {
            tree.add(1, a-1, b);
            debug("-- add [%d,%d) --", a-1, b);
            tree.print(1);
        } else {
            printf("%d\n", tree.getVal(1, a-1, b));
        }
    }
}
