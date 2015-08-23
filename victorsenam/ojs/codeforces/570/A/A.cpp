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

#define N 107

int n, m;
int a, maxi, maxv;
int can[N];

int main () {
    scanf("%d %d", &n, &m);
    
    for (int i = 0; i < m; i++) {
        maxi = 0;
        maxv = -1;
        for (int j = 0; j < n; j++) {
            scanf("%d", &a);
            if (a > maxv) {
                maxi = j;
                maxv = a;
            }
        }
        can[maxi]++;
    }

    maxi = 0;
    maxv = -1;
    for (int i = 0; i < n; i++) {
        if (can[i] > maxv) {
            maxi = i;
            maxv = can[i];
        }
    }
    printf("%d\n", maxi+1);
}
