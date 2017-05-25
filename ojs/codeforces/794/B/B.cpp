
#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define debug(...) {}
#endif

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

int n;
double h;

int main () {
    scanf("%d %lf", &n, &h);

    for (int i = 0; i <= n; i++) {
        double A = double(n-i)/double(n);
        printf("%.20lf\n", h*double(1.-sqrt(1.-A)));
    }
}
