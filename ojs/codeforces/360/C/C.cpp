#include <bits/stdc++.h>

using namespace std;

typedef long long int num;

const int N = 2007;
const int K = 2007;
const num MOD = 1000000007;

int n, k;
char str[N];
num s[N];
num pd[K][N];
num acc[N];

inline num mod (num a)
{ return (a%MOD + MOD)%MOD; }

int main () {
    scanf("%d %d", &n, &k);
    scanf(" %s", str);

    for (int i = 0; i < n; i++)
        s[i] = str[i]-'a';

    pd[0][0] = 1;
    for (int g = 0; g <= k; g++) {
        for (int i = 1; i <= n; i++) {
            num & r = pd[g][i];

            r = 0;
            acc[i] = mod(acc[i-1] + pd[g][i-1]);
            r = mod(r + mod(s[i-1]*acc[i]));

            int aux = n-i+1;
            for (int j = 0; j < i && g >= aux; j++) {
                r = r + (25ll-s[i-1])*pd[g-aux][i-j-1];
                aux += n-i+1;
            }
            r = mod(r);
        }
    }
    num res = 0;
    for (int i = 0; i <= n; i++)
        res = res + pd[k][i];
    printf("%I64d\n", mod(res));
}
