#include <bits/stdc++.h>

using namespace std;
typedef int num;
#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#else
#define debug(...) //
#endif


#define N 15

int v[N];
int n, l, r, x;

int test (int i, int mini, int maxi, int sum) {
    if (i >= n) {
        if (l <= sum && r >= sum && maxi-mini >= x) return 1;
        return 0;
    }

    return test(i+1, min(mini, v[i]), max(maxi, v[i]), sum + v[i]) + test(i+1, mini, maxi, sum);
}

int main () {
    scanf("%d %d %d %d", &n, &l, &r, &x);
    for (int i = 0; i < n; i++)
        scanf("%d", &v[i]);

    printf("%d\n", test(0, INT_MAX, 0, 0));
}
