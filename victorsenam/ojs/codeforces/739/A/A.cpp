#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define debug(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 1e5+7;

int n, m;
int l[N][2];

int main () {
    scanf("%d %d", &n, &m);

    int res = n+1;
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &l[i][0], &l[i][1]);
        res = min(res, l[i][1]-l[i][0]+1);
    }

    printf("%d\n", res);
    for (int i = 0; i < n; i++)
        printf("%d ", i%res);



}
