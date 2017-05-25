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

int n, t, k, d;

int main () {
    scanf("%d %d %d %d", &n, &t, &k, &d);

    int a = t*((n+k-1)/k);

    int fst = 0;
    int snd = d;
    while (n > 0) {
        if (fst < snd)
            fst += t;
        else
            snd += t;
        n -= k;
    }

    int b = max(fst, snd);
    if (a <= b)
        printf("NO\n");
    else
        printf("YES\n");
}
