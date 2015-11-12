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
        scanf("%lld", a+i);

    for (int i = 0; i < n/k; i++)
        scanf("%lld", b+i);

    for (int i = 0; i < k; i++)
        dak *= 10ll;

    for (int i = 0; i < n/k; i++) {
        num att = dak/a[i];
        if (dak%a[i])
            att++;

        num pot = 10;
        for (int j = 1; j < k; j++) {
            num rem = a[i] - (b[i]*pot)%a[i];
            if (rem == a[i])
                rem = 0;

            num up = pot-rem;
            if (up > 0) {
                att -= up/a[i];
                if (up%a[i])
                    att--;
            }

            pot *= 10;
        }

        res = (res*att)%MOD;
    }

    printf("%lld\n", res);
}
