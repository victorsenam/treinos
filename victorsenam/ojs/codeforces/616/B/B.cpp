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

int n, m;
int mini, maxi, a;
int main () {
    scanf("%d %d", &n, &m);

    maxi = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &mini);
        for (int j = 1; j < m; j++) {
            scanf("%d", &a);
            mini = min(mini, a);
        }

        maxi = max(maxi, mini);
    }
    printf("%d\n", maxi);
}
