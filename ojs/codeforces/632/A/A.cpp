#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef double db;

ll n, p;
ll r;
char str[20];
bool v[41];

int main () {
    scanf("%lld %lld", &n, &p);

    for (int i = 0; i < n; i++) {
        scanf(" %s", str);
        v[i] = (str[4] == 'p');
    }
    
    ll c = 0;
    ll r = 0;
    for (int i = n-1; i >= 0; i--) {
        r += p*c;
        c *= 2;

        if (v[i]) {
            c++;
            r += p/2;
        }
    }

    printf("%lld\n", r);
}
