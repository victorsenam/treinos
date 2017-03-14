#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef int num;
#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#else
#define debug(...) //
#endif

#define N 200008

ll n;
int w;
ll v[N];
ll maxi;
bool maxb;

int main () {
    scanf("%d %d", &n, &w);
    for (int i = 0; i < 2*n; i++) 
        scanf("%d", v+i);

    sort(v, v+2*n);

    if (3*n*v[0] >= (3*n*v[n])/2) {
        maxi = (3*n*v[n])/2;
        maxb = (3*n*v[n])%2;
    } else {
        maxi = 3*n*v[0];
        maxb = 0;
    }

    if (w <= maxi) {
        maxi = w;
        maxb = 0;
    }

    printf("%d", maxi);
    if (maxb)
        printf(".5");

    printf("\n");
}
