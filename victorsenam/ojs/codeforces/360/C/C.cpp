#include <bits/stdc++.h>

using namespace std;

typedef long long num;

const num MOD = 1e9+7;
const int N = 2007;

int n, k;
char str[N];
num memo[N][N][3];
bool visi[N][N][3];

inline num mod (num a)
{ return (a%MOD + MOD)%MOD; }

num pd (int i, int k, int pre) {
    if (k < 0)
        return 0;
    if (i == n)
        return (!k)&&(pre!=1);

    num & me = memo[i][k][pre];
    if (visi[i][k][pre])
        return me;
    visi[i][k][pre] = 1;

    me = 0;

    if (pre == 0) { // leq
        me = mod(me + pd(i+1, k, 0));
        me = mod(me + mod(num(str[i]-'a')*pd(i+1, k, 2)));
    } else if (pre == 1) { // gt
        me = mod(me + pd(i+1, k, 1));
        me = mod(me + mod(num('z'-str[i])*pd(i+1, k, 2)));
    } else {
        me = mod(me + pd(i+1, k, 0));
        me = mod(me + pd(i+1, k-(n-i), 1));
        me = mod(me + mod(num(str[i]-'a')*pd(i+1, k, 2)));
        me = mod(me + mod(num('z'-str[i])*pd(i+1, k-(n-i), 2)));
    }


    printf("%d %d [%d] -> %lld\n", i, k, pre, me);
    return me;
}

int main () {
    scanf("%d %d %s", &n, &k, str);

    printf("%lld\n", mod(pd(0, k, 2)));
}
