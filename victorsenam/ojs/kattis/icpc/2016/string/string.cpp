#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;

const int N = 1e2+7;

int n;
int a[N];
int K;
int visi[N][N][N][2];
int memo[N][N][N][2];

int pd (int i, int k, int x, int c) {
    if (k == 1)
        c = 1;
    if (x < 0 || k <= 0) return 0;
    if (x == 0) {
        i++;
        x = a[i];
    }
    if (i == n) 
        return ((k == K + 1) && c);
    if (k > K)
        return 0;

    int & me = memo[i][k][x][c];
    if (visi[i][k][x][c] == K) return me;
    visi[i][k][x][c] = K;

    me = ((c && pd(i, k+1, x-k, 1)) || pd(i, k-1, x-k+1, 0));
    return me;
}

int main () {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    for (K = a[0]; K > 0; K--)
        if (pd(0, K, a[0]-K, 0)) {
            printf("%d\n", K);
            return 0;
        }
    
    printf("no quotation\n");
}
