#include <bits/stdc++.h>

using namespace std;

const int N = 1000;

int dp[N];
int acc[N];
int n;
int ts;

int calc (int i) {
    if (i >= N)
        return dp[100+(i%34)];
    else
        return dp[i];
}

int main () {
    n = N;
    dp[0] = 0;
    dp[1] = 1;
    for (int i = 2; i <= n; i++) {
        acc[dp[i-2]] = i;

        for (int j = 0; j <= i-3; j++)
            acc[(dp[j]^dp[i-j-3])] = i;
        
        dp[i] = 0;
        while (acc[dp[i]] == i)
            dp[i]++;
    }
    for(int i = 6; i <= n; i += 4)
        printf("dp[%d] = %d\n", i, dp[i]);
    return 0;

    scanf("%d", &ts);
    memset(acc, 0, sizeof 0);
    for (int cs = 1; cs <= ts; cs++) {
        scanf("%d", &n);
        bool res = 0;
        if (n&1) {
            res = 1;
        } else if (n < N) {
            res = dp[n];
        } else {
            for (int i = 0; !res && i < min(N, n-2); i+=2)
                if (!(dp[i]^calc(n-i-3)))
                    res = 1;
        }

        printf("Case #%d: ", cs);
        if (res)
            printf("UDIN\n");
        else
            printf("UCOK\n");
            
    }
}
