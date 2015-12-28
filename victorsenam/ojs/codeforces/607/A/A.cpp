#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef int num;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n");}
#else
#define DEBUG(...) {}
#endif

const int N = 100007;

int ia[N], ib[N], p[N];
int a[N], b[N];
int n;
int res[N];
int maxi;

bool v_cmp (int i, int j)
{ return ia[i] < ia[j]; }

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d %d", ia+i, ib+i);
        p[i] = i;
    }

    sort(p, p+n, v_cmp);

    for (int i = 0; i < n; i++) {
        a[i] = ia[p[i]];
        b[i] = ib[p[i]];
    }

    maxi = 0;
    for (int i = 0; i < n; i++) {
        int l = lower_bound(a, a+i, a[i]-b[i]) - a;
        if (l == 0) {
         //   printf("%d -> %d ", a[i], -1);
            res[i] = 1;
        } else {
           // printf("%d -> %d ", a[i], a[l-1]);
            res[i] = res[l-1] + 1;
        }
        //printf("%d\n", res[i]);
        maxi = max(maxi, res[i]);
    }
    printf("%d\n", n-maxi);
}
