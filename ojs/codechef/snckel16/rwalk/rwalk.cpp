#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 502;
const int K = 501;

int memo[N][N*N];
int a[2][N];
int r[2];
int t, n;
char c;
int sum;

int main () {
    scanf("%d", &t);

    while (t--) {
        scanf("%d", &n);
        n++;

        scanf("%d", &a[0][0]);

        for (int i = 1; i < n; i++) {
            scanf(" %c", &c);
            scanf("%d", &a[i&1][i/2]);
        }

        if (n <= 3) {
            printf("NO\n");
            continue;
        }

        for (int p = 0; p < 2; p++) {
            int m = (n+!p)/2;
            a[p][m] = 0;
            sum = 0;
            for (int i = 0; i < m; i++)
                sum += a[p][i];

            for (int i = m; i >= 0; i--) {
                sum -= a[p][i];
                for (int s = 0; s <= sum; s++) {
                    if (i == m) memo[i][s] = s;
                    else memo[i][s] = min(memo[i+1][abs(s+a[p][i])], memo[i+1][abs(s-a[p][i])]);
                }
            }
            r[p] = memo[0][0];
        }
        printf("%d\n", r[0]+r[1]);
    }
}
