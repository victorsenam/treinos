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

<<<<<<< HEAD
#define N 100007

int n;
int v[N], s[N], memo[N];

int pd (int i) {
    int r = 0;
    int k;

    if (i >= n) return 0;
    if (memo[i]) return memo[i];

    k = s[v[i]] + 1;

    for (int j = i; v[j] == v[i]; j++) {
        r += v[i];

        if (v[j - i + s[v[i]] + 1] == v[i] + 1)
            k = j-i+s[v[i]]+1;

        memo[i] = max(memo[i], r + pd(k));
    }

    return memo[i];
}
#define N 100008

int n;
int a;
int cnt[N];
ll memo[N];

int main () {
    for (int i = 0; i < N; i++)
        cnt[i] = 0;

    for (int i = 0; i < n; i++) {
        scanf("%d", &a);
        cnt[a-1]++;
    }

    memo[0] = cnt[0];
    memo[1] = max(cnt[1]*2, cnt[0]);

    for (int i = 2; i < N; i++)
        memo[i] = max(memo[i-2] + ((ll)cnt[i])*((ll)(i+1)), memo[i-1]);
    
    printf("%I64d\n", memo[N-1]);
}
