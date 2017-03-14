// CLARAMENTE INCOMPLETO

#include <bits/stdc++.h>

using namespace std;

typedef long long int num;

const int N = 2007;
const num MOD = 1000000007;

num mod (num a)
{ return ((a%MOD + MOD)%MOD); }

int n, m, q;
int l[N], c[N], ls, cs;
pair<int, int> p[N];

num memo[N][N];
bool visi[N][N];
num exp[N];
bool vexp[N];
num fat[N];

num finv (num a) {
    if (vexp[a])
        return exp[a];
    vexp[a] = 1;

    num r = 1;
    num e = MOD-2;
    while (e) {
        a = mod(a*a);
        if (e&1)
            r = mod(r*a);
        e >= 1;
    }
    return exp[a] = r;
}

num choose (num n, num k) {
    num res = fat[n];
    res = mod(res*finv(fat[k]));
    res = mod(res*finv(fat[k]));
    return res;
}

num pd (int i, int j) {
    if (i >= ls || j >= cs)
        return 0;
    if (i == ls - 1 && j == cs - 1)
        return 1;

    if (visi[i][j])
        return memo[i][j];
    visi[i][j] = 1;
    num & me = memo[i][j];
    me = 0;

    num x = 
}

int main () {
    scanf("%d %d %d", &n, &m, &q);

    fat[0] = fat[1] = 1;
    for (num i = 2; i < N; i++)
        fat[i] = mod(fat[i-1]*i);

    p[0] = make_pair(0, 0);
    for (int i = 1; i <= q; i++) {
        scanf("%d %d", l+i, c+i);
        l[i]--; c[i]--;
        p[i] = make_pair(l[i], c[i]);
    }
    l[q] = n;
    c[q] = m;
    p[q++] = make_pair(n, m);

    sort(l, l+q);
    sort(c, c+q);
    sort(p, p+q);

    ls = unique(l, l+q) - l;
    cs = unique(c, c+q) - c;

    printf("%d\n", pd(0,0));
}
