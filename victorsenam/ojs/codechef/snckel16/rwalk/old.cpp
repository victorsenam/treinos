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

int memo[K*N][N];
char visi[K*N][N];
int acc[2][N];
int a[2][N];
int s[2];
int r[2];
int t, n;
char c;
int turn;
int p;

int pd (int sum, int i) {
    sum = max(sum, -sum);
    if (i >= (n+!p)/2) return sum;
    if (sum > acc[p][i]) return sum-acc[p][i];
    
    int & me = memo[sum][i];
    if (visi[sum][i] == turn)
        return me;
    visi[sum][i] = turn;

    me = min(pd(sum+a[p][i], i+1), pd(sum-a[p][i], i+1));
    return me;
}

bool cmp_t (int i, int j) {
    return i > j;
}

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

        for (p = 0; p < 2; p++) {
            sort(a[p], a[p]+(n+!p)/2, cmp_t);
            acc[p][(n+!p)/2] = 0;
            for (int i = (n+!p)/2-1; i >= 0; i--)
                acc[p][i] = acc[p][i+1] + a[p][i];

            turn++;
            r[p] = pd(0, 0);
        }

        printf("%d\n", r[0]+r[1]);
    }
}
