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

#define N 100005

int n;
long long int a[N];

int main () {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%I64d", a+i);

    for (int i = 0; i < n; i++) {
        long long int mini = LLONG_MAX;
        if (i-1 >= 0)
            mini = min(mini, a[i]-a[i-1]);
        if (i+1 < n)
            mini = min(mini, a[i+1]-a[i]);
        
        long long int maxi = 0;
        maxi = max(maxi, a[i]-a[0]);
        maxi = max(maxi, a[n-1]-a[i]);

        printf("%I64d %I64d\n", mini, maxi);
    }


}
