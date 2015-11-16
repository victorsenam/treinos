#include <bits/stdc++.h>

using namespace std;

const int N = 2007;

typedef long long int num;

double memo[N][N][2][2];
int tl[N], tr[N];
bool visi[N][N][2][2];
num n, h;
num x[N];
double p;

double pd (int i, int j, bool l, bool r) {
    if (visi[i][j][l][r])
        return memo[i][j][l][r];
    visi[i][j][l][r] = 1;

    double & me = memo[i][j][l][r];

    if (i + 1 == j) {
        me = 0.0;

    } else {
        cl[i][j] = 0.5*p;
        cr[i][j] = 0.5*(1.0-p);
        memo[i][j] = 0.0;

        memo[i][j] += 0.5*p*pd(i+1, j, min(h, x[i+1]-x[i]), r, cl[i][j]);
        memo[i][j] += 0.5*(1.0-p)*pd(i, j-1, l, min(h, x[j-1]-x[j-2]), cr[i][j]);

        int att = min(tr[i], j);
        memo[i][j] += 0.5*(1.0-p)*(x[att-1]-x[i]);
        if (att == j)
            cr[i][j] += 0.5*(1.0-p);
        else
            memo[i][j] += 0.5*(1.0-p)*(h + pd(att, j, min(h, x[att]-x[att-1]), 0, 0.5*(1.0-p)));

        att = max(tl[j-1], i-1);
        memo[i][j] += 0.5*(p)*(x[j-1]-x[att+1]);
        if (att == i-1)
            cl[i][j] += 0.5*p;
        else
            memo[i][j] += 0.5*p*(h + pd(i, att+1, 0, min(h, x[att+1]-x[att]), 0.5*p));
    }

    return memo[i][j] + cl[i][j]*l + cr[i][j]*r;
}

int main () {
    scanf("%I64d %I64d %lf", &n, &h, &p);

    for (int i = 0; i < n; i++)
        scanf("%I64d", x+i);
    sort(x, x+n);

    int i = 0;
    while (i < n) {
        int att = i+1;
        while (att < n && x[att] - x[att-1] < h) att++;
        for (int j = i; j < att; j++)
            tr[j] = att;
        i = att;
    }

    i = n-1;
    while (i >= 0) {
        int att = i-1;
        while (att >= 0 && x[att+1] - x[att] < h) att--;
        for (int j = i; j > att; j--)
            tl[j] = att;
        i = att;
    }

    printf("%lf\n", pd(0, n, 0, 0));
}
