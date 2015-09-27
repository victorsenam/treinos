#include<bits/stdc++.h>
using namespace std;
typedef long long num;
int tc;
num a,b,cn,cd,d;

num gcd(num a, num b)
{ return ( b == 0ll) ? a : gcd(b,a%b); }

int main()
{
    scanf("%d", &tc);

    while (tc--) {
        scanf("%lld/%lld", &a, &b);

        while (a != b) {
            if (a > b) {
                printf("R");
                a -= b;
                swap(a,b);
            } else {
                printf("L");
                b -= a;
                swap(a,b);
            }
            d = gcd(a, b);
            a /= d;
            b /= d;
        }

        printf("\n");
    }
}
