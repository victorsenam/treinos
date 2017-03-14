#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 30;
const int K = 1123456;

int memo[K];
int turn;
int n, m;
int v[N];
int t;

int main () {
    scanf("%d", &t);
    while (turn++ < t) {
        scanf("%d %d", &n, &m);
        for (int i = 0; i < n; i++)
            scanf("%d", &v[i]);

        memo[0] = 0;
        for (int i = 1; i <= m; i++) {
            memo[i] = K;
            for (int j = 0; j < n; j++)
                if (v[j] <= i)
                    memo[i] = min(memo[i], memo[i-v[j]]+1);
        }
        printf("%d\n", memo[m]);
    }
}
