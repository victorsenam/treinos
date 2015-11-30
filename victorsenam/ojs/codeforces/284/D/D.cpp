#include <bits/stdc++.h>

using namespace std;

const int N = 200007;

typedef long long int num;

int n;
num a[N];
int s[N][2];
num v[N][2];

num dfs (int u, bool d) {
    if (u <= 0 || u > n)
        return 0;
    if (s[u][d] == 1)
        return -1;
    else if (s[u][d] == 2)
        return v[u][d];

    s[u][d] = 1;

    if (d)
        v[u][d] = dfs(u-a[u], 0);
    else
        v[u][d] = dfs(u+a[u], 1);

    if (v[u][d] >= 0)
        v[u][d] += a[u];

    s[u][d] = 2;
    return v[u][d];
}

int main () {
    scanf("%d", &n);

    for (int i = 2; i <= n; i++)
        scanf("%I64d", a+i);

    s[1][1] = s[1][0] = 1;

    for (num i = 2; i <= n; i++) {
        num val = dfs(i, 1);

        if (val == -1)
            printf("-1\n");
        else
            printf("%I64d\n", val+i-1ll);
    }

}
