#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define LLD "%lld"
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define LLD "%I64d"
#define DEBUG(...) {}
#endif

const int N = 100007;

ll a, v[N], t[N];
ll d;
int n;
double mint;

double finTime (int i) {
    double s0 = double(v[i]*v[i])/double(2.*a);
    if (s0 >= d) {
        return sqrt(double(2.*d)/double(a)) + double(t[i]);
    }
    
    return (double(d)-s0)/double(v[i]) + double(v[i])/double(a) + double(t[i]);
}

int main () {
    scanf("%d " LLD LLD, &n, &a, &d);

    mint = -1./0.;

    for (int i = 0; i < n; i++) {
        scanf(LLD LLD, t+i, v+i);

        mint = max(mint, finTime(i));
        printf("%.20f\n", mint);
    }
}
