#include <bits/stdc++.h>

using namespace std;

typedef long long num;

const int N = 100007;
const num MOD = 1000000007;

num mod (num a) {
    return (a%MOD + MOD)%MOD;
}

int visi[N][2][2];
num memo[N][2][2];
char a[N], b[N];
int n;

num pd (int i, bool up, bool down) {
    if (i == n)
        return (up&&down);

    if (visi[i][up][down])
        return memo[i][up][down];
    visi[i][up][down] = 1;

    num loc = 0;
    if (a[i] == '?' && b[i] == '?') {
        for (int x = '0'; x <= '9'; x++)
            for (int y = '0'; y <= '9'; y++)
                loc = mod(loc + pd(i+1, ((x<y)||up), ((x>y)||down)));
    } else if (a[i] == '?') {
        for (int x = '0'; x <= '9'; x++)
            loc = mod(loc + pd(i+1, ((x<b[i])||up), ((x>b[i])||down)));
    } else if (b[i] == '?') {
        for (int x = '0'; x <= '9'; x++)
            loc = mod(loc + pd(i+1, ((x>a[i])||up), ((x<a[i])||down)));
    } else {
        loc = pd(i+1, (up||a[i]<b[i]), (down||a[i]>b[i]));
    }
    
    memo[i][up][down] = loc;
    return loc;
}

int main () {
    scanf("%d", &n);
    scanf(" %s %s", a, b);

    printf("%I64d\n", pd(0, 0, 0));
}
