#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
typedef int num;
#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#else
#define debug(...) //
#endif

#define N 1000
#define MOD 1000000007

int n;
ll k[N];
ll s[N];
ll siz; 
ll nume;
ll deno;
ll mfact[N*(N+7)];

ll fact (ll n) {
    if (mfact[n]) return mfact[n];
    return mfact[n] = (n*fact(n-1))%MOD;
}

ll fexp (ll n, int exp) {
    if (exp == 0) 
        return 1;
    if (exp == 1) 
        return n;
    if (exp%2)
        return (n*fexp(n, exp-1))%MOD;
    ll aux = fexp(n, exp/2);
    return (aux*aux)%MOD;
}

int main () {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", k+i);

    mfact[0] = mfact[1] = 1;

    siz = k[0];
    s[0] = 1;
    for (int i = 1; i < n; i++) {
        nume = fact(siz+k[i]-1);
        deno = (fact(siz)*fact(k[i]-1))%MOD;
        s[i] = (s[i-1]*((nume*fexp(deno, MOD-2))%MOD))%MOD;
        siz += k[i];
    }

    printf("%d\n", (int) s[n-1]);
}
