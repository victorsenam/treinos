#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define LLD "%lld"
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define LLD "%I64d"
#define DEBUG(...) {}
#endif

const int N = 300002;
const int MAX = 4*N;

int n, m, c;
int x[N];
double p[N];
int a[N], b[N];
int prm[N];
double acc[N];
double win[N];

bool cmp_t (int i, int j) {
    return a[i] < a[j];
}

struct seg {
    int esq[MAX], dir[MAX];
    double sum[MAX];
    int lazy[MAX];

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
            lazy[root] += v;
            refresh(root);
            return;
        }
        if (e >= dir[root] || d <= esq[root])
            return;

        update(2*root, e, d, v);
        update(2*root+1, e, d, v);
        sum[root] = sum[2*root] + sum[2*root+1];

    }

    double getVal (int root, int e, int d) {
        refresh(root);
        if (e <= esq[root] && d >= dir[root]) return sum[root];
        if (e >= dir[root] || d <= esq[root]) return 0;
        return getVal(2*root, e, d) + getVal(2*root+1, e, d);
    }

    void refresh (int root) {
        sum[root] += (acc[dir[root]+1]-acc[esq[root]])*lazy[root];
        if (dir[root] - esq[root] > 1) {
            lazy[2*root] += lazy[root];
            lazy[2*root+1] += lazy[root];
        }
        lazy[root] = 0;
    }
};
seg tree;


double solve (int i, int j) {
    return win[j+1] - win[i] + tree.getVal(1, i, j+1);
}

double bt (int i) {
    int lo = i;
    int hi = n;

    while (lo + 3 < hi) {
        int q1 = (lo+lo+hi)/3;
        int q2 = (lo+hi+hi)/3;
        if (solve(i, q1) >= solve(i, q2))
            hi = q2;
        else
            lo = q1;
    }

    return solve(i, lo);
}

int main () {
    scanf("%d %d %d", &n, &m, &c);
    tree.build(1, 0, n);

    for (int i = 1; i <= n; i++)
        scanf("%d", x+i);

    acc[0] = 0.;
    for (int i = 1; i <= n; i++) {
        scanf("%lf", acc+i);
        acc[i] /= 100.;
        if (i)
            acc[i] += acc[i-1];
    }


    for (int i = 0; i < m; i++) {
        scanf("%d %d", a+i, b+i);
        tree.update(1, a[i], b[i]+1, 1);
        DEBUG("coloca um cara entrando em %d e saindo em %d : %.20f\n", a[i], b[i], tree.getVal(0, n, 1));
        prm[i] = i;
        win[a[i]+1] += .5*(x[b[i]]-x[a[i]]);
    }
    DEBUG("%.20f\n", tree.getVal(1, 0, n));
    sort(prm, prm+n, cmp_t);

    for (int i = 0; i <= n; i++)
        win[i] += win[i-1];

    int k = 0;
    double res = 0.;
    double loc;

    for (int i = 0; i < n; i++) {
        while (k < n && a[prm[k]] <= i) {
            tree.update(1, a[prm[k]], b[prm[k]]+1, -1);
            k++;
        }

        res = max(res, bt(i));
    }

    printf("%.20f\n", res);
}
