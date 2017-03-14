#include <bits/stdc++.h>

using namespace std;
typedef int num;
#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#else
#define debug(...) //
#endif

#define N 100001
#define MAX 4*N

struct no {
    int ie, fe, id, fd, im, fm;
};

struct seg {
    no nos[MAX];
    no res;
    no temp;
    int acc[N];
    int cr, er;

    void criaAcc (int siz) {
        acc[0] = 0;
        for (int i = 1; i <= siz; i++) {
            scanf("%d", &acc[i]);
            acc[i] += acc[i-1];
        }
    }

    void getInt(int c1, int e1, int c2, int e2) {
        debug("%d %d ou %d %d", c1, e1, c2, e2);
        if (acc[e1] - acc[c1] > acc[e2] - acc[c2]) {
            cr = c1;
            er = e1;
            return;
        }
        if (acc[e1] - acc[c1] < acc[e2] - acc[c2]) {
            cr = c2;
            er = e2;
            return;
        } 
        if (e1 - c1 > e2 - c2) {
            cr = c1;
            er = e1;
            return;
        }
        cr = c2;
        er = e2;
    }

    no joinSols(no a, no b) {
        getInt(a.ie, a.fe, a.ie, b.fe);
        temp.ie = cr;
        temp.fe = er;

        getInt(b.id, b.fd, a.id, b.fd);
        temp.id = cr;
        temp.fd = er;

        getInt(a.im, a.fm, b.im, b.fm);
        temp.im = cr;
        temp.fm = er;
        debug("temp = [%d,%d) [%d,%d) [%d,%d)", temp.ie, temp.fe, temp.im, temp.fm, temp.id, temp.fd);

        getInt(temp.im, temp.fm, a.id, b.fe);
        temp.im = cr;
        temp.fm = er;

        debug("a = [%d,%d) [%d,%d) [%d,%d)", a.ie, a.fe, a.im, a.fm, a.id, a.fd);
        debug("b = [%d,%d) [%d,%d) [%d,%d)", b.ie, b.fe, b.im, b.fm, b.id, b.fd);
        debug("temp = [%d,%d) [%d,%d) [%d,%d)", temp.ie, temp.fe, temp.im, temp.fm, temp.id, temp.fd);

        return temp;
    }


    no getQuery (int root, int e, int d) {
        debug("%d -> [%d,%d) on [%d,%d)", root, e, d, nos[root].ie, nos[root].fd);
        if (nos[root].ie >= e && nos[root].fd <= d)
            return nos[root];
        
        if (e >= nos[2*root].fd || d <= nos[2*root].ie)
            return getQuery(2*root+1, e, d);
        if (e >= nos[2*root+1].fd || d <= nos[2*root+1].ie)
            return getQuery(2*root, e, d);

        return joinSols(getQuery(2*root, e, d), getQuery(2*root+1, e, d));
    }

    void build (int root, int e, int d) {
        nos[root].ie = nos[root].id = nos[root].im = e;
        nos[root].fe = nos[root].fd = nos[root].fm = d;

        if (e + 1 == d)
            return;

        build(2*root, e, e+(d-e)/2);
        build(2*root+1, e+(d-e)/2, d);

        getInt(nos[2*root].ie, nos[2*root].fe, nos[2*root].ie, nos[2*root+1].fe);
        nos[root].ie = cr;
        nos[root].fe = er;

        getInt(nos[2*root+1].id, nos[2*root+1].fd, nos[2*root].id, nos[2*root+1].fd);
        nos[root].id = cr;
        nos[root].fd = er;

        getInt(nos[2*root].im, nos[2*root].fm, nos[2*root+1].im, nos[2*root+1].fm);
        nos[root].im = cr;
        nos[root].fm = er;

        getInt(nos[root].im, nos[root].fm, nos[2*root].id, nos[2*root+1].fe);
        nos[root].im = cr;
        nos[root].fm = er;
    }
};

int t, n, q, a, b;
seg tree;

int main () {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        tree.criaAcc(n);
        tree.build(1, 0, n);

        scanf("%d", &q);
        for (int i = 0; i < q; i++) {
            scanf("%d %d", &a, &b);
            tree.res = tree.getQuery(1, a-1, b);
            printf("%d %d\n", tree.acc[tree.res.fm] - tree.acc[tree.res.im], tree.res.fm - tree.res.im);
        }
    }
}
