#include <bits/stdc++.h>
using namespace std;
typedef long long num;

const int N = 52;

int cnt, grid[N][N], n, m, w, b;

int main()
{
    freopen("alter.in", "r", stdin);
    freopen("alter.out", "w", stdout);
    scanf(" %d%d", &n, &m);
    printf("%d\n", n/2 + m/2);
    for(int i=2;i<n+1;i+=2)
        printf("%d %d %d %d\n", i, 1, i, m), cnt++;
    for(int j=2;j<m+1;j+=2)
        printf("%d %d %d %d\n", 1, j, n, j), cnt++;
    assert(n/2 + m/2 == cnt);
}
