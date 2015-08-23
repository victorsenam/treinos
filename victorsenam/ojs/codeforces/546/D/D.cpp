#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%d| ", __LINE__); fprintf(stderr, __VA_ARGS__)
#else
#define debug(...) //
#endif

#define N 5000001

using namespace std;

typedef int num;

int memo[N];
int acc[N];
int t, a, b;
vector<int> primes;

int fact(int i) {
    int j;
    if (i < 2) return 0;
    if (memo[i] > 0) return memo[i];

    for (int k = 0; k < primes.size() &&  primes[k]*primes[k] <= i; k++) {
        j = primes[k];
        if (i%j) continue;

        return memo[i] = fact(j) + fact(i/j);
    }

    return memo[i] = 1;
}

int main () {
    for (int i = 0; i <= N; i++) memo[i] = 0;
    
    for (int i = 2; i <= N; i++) {
        if (memo[i]) continue;
        memo[i] = 1;
        primes.push_back(i);
        for (int j = 2; j*i <= N; j++)
            memo[j*i] = -1;
    }
    for (int i = 2; i < primes.size(); i++) {
        for (int j = 2; j*primes[i] <= N; j++)
            memo[j*primes[i]] = 1 + fact(j);
    }

    acc[0] = acc[1] = 0;
    for (int i = 2; i <= N; i++)
        acc[i] = acc[i-1] + fact(i);

    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &a, &b);
        
        printf("%d\n", acc[a] - acc[b]);
    }
}
