#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef int num;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 200000;

int n;
int deg[N];
int a, b;
ll x, y;
int cnt;
int sum;

int main () {
    scanf("%d %lld %lld", &n, &x, &y);

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &a, &b);
        a--; b--;
        deg[a]++;
        deg[b]++;
        cnt += (deg[a] == n-1);
        cnt += (deg[b] == n-1);
    }
    
    if (x == y)
        printf("%lld\n", x*(n-1));
    else if (x > y) {
        if (cnt)
            printf("%lld\n", y*(n-2) + x);
        else
            printf("%lld\n", y*(n-1));
    } else {

    }

}
