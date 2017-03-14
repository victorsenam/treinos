#include <bits/stdc++.h>

using namespace std;
typedef long long int num;

const int N = 100007;
const num MOD = 1000000007ll;

int n;
int k;
num a[N], b[N];

int main () {
    num res = 1;
    num dak = 1;

    scanf("%d %d", &n, &k);

    for (int i = 0; i < n/k; i++)
        scanf("%I64d", a+i);

    for (int i = 0; i < n/k; i++)
        scanf("%I64d", b+i);

    for (int i = 1; i < k; i++)
        dak *= 10ll;

    for (int i = 0; i < n/k; i++) {
        num att = (dak*10)/a[i];
        if ((dak*10)%a[i])
            att++;

        num rem = (a[i] - (b[i]*dak)%a[i])%a[i];
        if (rem < 0)
            rem += a[i];
        num up = dak - rem;
        if (up > 0) {
            att -= up/a[i];
            if (up%a[i])
                att--;
        }

        res = (res*att)%MOD;
    }

    printf("%I64d\n", res);
}
