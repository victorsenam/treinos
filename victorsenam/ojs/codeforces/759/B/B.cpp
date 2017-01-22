#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;

const int N = 1e5+7;

int n;
int t[N];
int memo[N];

int main () {
    scanf("%d", &n);

    memo[0] = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &t[i]);
        memo[i] = memo[i-1] + 20;

        int p = upper_bound(t+1, t+i, t[i] - 90) - (t+1);
        memo[i] = min(memo[i], memo[p] + 50);
        //printf("%d volta %d : %d\n", i, 90, p);

        p = upper_bound(t+1, t+i, t[i] - 1440) - (t+1);
        memo[i] = min(memo[i], memo[p] + 120);
        //printf("%d volta %d : %d\n", i, 1440, p);

        printf("%d\n", memo[i]-memo[i-1]);
    }

}
