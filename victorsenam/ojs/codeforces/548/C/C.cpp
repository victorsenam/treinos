#include <bits/stdc++.h>

using namespace std;
typedef int num;
#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#define D
#else
#define debug(...) //
#define D //
#endif

#define N 1000000

int n, k, l;
int mod, h1, a1, x1, y, h2, a2, x2, y2, l1, l2, mdc;
int xr, yr, x;
int t1[N], t2[N];

int euclid(int a, int b) {
    if (b == 0) {
        k = 1;
        l = 0;
        return a;
    }
    int m = euclid(b, a%b);
    int aux = k;
    k = l;
    l = aux - (a/b)*l;
    return m;
}

int main () {
    scanf("%d", &mod);
    scanf("%d %d", &h1, &a1);
    scanf("%d %d", &x1, &y);
    scanf("%d %d", &h2, &a2);
    scanf("%d %d", &x2, &y2);

    for (int i = 0; i < mod; i++) 
        t1[i] = t2[i] = -1;

    l1 = 0;
    while (t1[h1] == -1) {
        t1[h1] = l1++;
        h1 = (x1*h1 + y)%mod;
    }
    l1 = l1 - 1 - t1[h1];
    if (t1[a1] == -1) {
        printf("-1\n");
        return 0;
    }
    
    // for (int i = 0; i < mod; i++)
    //     printf("%d ", t1[i]);
    // printf("\n");

    l2 = 0;
    while (t2[h2] == -1) {
        t2[h2] = l2++;
        h2 = (x2*h2 + y2)%mod;
    }
    l2 = l2 - 1 - t2[h2];
    if (t2[a2] == -1) {
        printf("-1\n");
        return 0;
    }

    // for (int i = 0; i < mod; i++)
    //     printf("%d ", t2[i]);
    // printf("\n");

    k = 1; l = 0;
    mdc = euclid(l1, -l2);
    
    debug("mdc %d to %d\n", mdc, t2[a2]-t1[a1]);
    if ((t2[a2] - t1[a1])%mdc) {
        printf("-1\n");
        return 0;
    }

    debug("%d %d", k, l);
    k *= (t2[a2]-t1[a1])/mdc;
    debug("%d", k);
    
    x = -k*mdc/l2;
    x = k + l2*x/mdc;
    while (x < 0) x += l2/mdc;

    printf("%d\n", l1*x+t1[a1]);
}
