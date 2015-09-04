// Quase lá

#include <bits/stdc++.h>

using namespace std;

const int K = 28;
const int N = 5007;

int n, m, t;
int sum[2][N][K];
int tot[K];
int memo[N][N];
char str[2][N];

int opens (int i, int j) {
}

int pd (int i, int j) {
    if (i == n && j == m)
        return 0;

    int & m = memo[i][j];

    if (m == -1)
        return m;
    
    m = INT_MAX;

    if (i < n)
        m = min(m, pd(i+1, j));
    if (j < m)
        m = min(m, pd(i, j+1));

    m = max(m, m + opens(i, j));
    return m;
}

int main () {
    scanf("%d", &t);

    while (t--) {
        scanf(" %s %s", str, str+1);

           
    }
}
