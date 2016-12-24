#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef double db;

const int N = 5e5+7;

int n;
ll a[N];
ll s;
ll c;
ll r;
char str[N];

int main () {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
        s += a[i];
    }
    scanf(" %s", str);
    for (int i = 0; i < n; i++)
        if (str[i] == 'B')
            c += a[i];
    
    r = max(r, c);
    r = max(r, s-c);

    for (int i = 0; i < n; i++) {
        if (str[i] == 'B')
            c -= a[i];
        else
            c += a[i];

        r = max(r, c);
        r = max(r, s-c);
    }

    printf("%lld\n", r);
}
