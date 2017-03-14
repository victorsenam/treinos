#include <bits/stdc++.h>

using namespace std;
typedef int num;

#define N 300007
#define MAX 4*N+1

struct seg {
    int esq[MAX], dir[MAX];
    num val[MAX];

    void build (int root, int e, int d) {
        esq[root] = e;
        dir[root] = d;
        val[root] = 0;
 //       printf("%d [%d,%d)\n", root, e, d);
        if (d-e==1) return;
        build(2*root, e, e+(d-e)/2);
        build(2*root+1, e+(d-e)/2, d);
    }

    void update(int root, int e, int d, int x) {
 //       printf("call %d [%d,%d) to %d\n", root, e, d, x);
        if (val[root] != 0)
            return;
        if (esq[root] >= e && dir[root] <= d) {
 //           printf("set %d [%d,%d) to %d\n", root, e, d, x);
            val[root] = x;
            return;
        }
        if (esq[root] >= d || dir[root] <= e)
            return;
        update(root*2, e, d, x);
        update(root*2+1, e, d, x);
    }

    void printit(int root, num upper) {
        num tp = upper;
        if (val[root] != 0)
            tp = val[root];
        if (dir[root] - esq[root] == 1) {
            printf("%d ", tp);
            return;
        }
        printit(2*root, tp);
        printit(2*root+1, tp);
    }
};

seg tree;
int n, m;
int a, b, x;

int main () {
    scanf("%d %d", &n, &m);
    tree.build(1, 0, n);
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &a, &b, &x);
        if (a == x) {
            tree.update(1, a, b, x);
        } else if (b == x) {
            tree.update(1, a-1, b-1, x);
        } else {
            tree.update(1, a-1, x-1, x);
            tree.update(1, x, b, x);
        }
    }
    tree.printit(1, 0);
    printf("\n");
}
