#include <bits/stdc++.h>

using namespace std;
typedef long long int num;

const int N = 100007;

int n, m, k;
num q[N];
num acc[N];
int l[N], r[N], d[N], v[N];

int main ( ){
    scanf("%d %d %d", &n, &m, &k);

    for (int i = 0; i < n; i++)
        scanf("%I64d", v+i);

    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", l+i, r+i, d+i);
        l[i]--;
    }

    for (int i = 0; i < k; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        acc[--x]++;
        acc[y]--;
    }
    
    num ac = 0;
    for (int i = 0; i < m; i++) {
        ac += acc[i];
        acc[i] = 0;
        q[i] = ac;
    }
    ac += acc[m];
    acc[m] = 0;
    assert(ac == 0);

    for (int i = 0; i < m; i++) {
        acc[l[i]] += d[i]*q[i];
        acc[r[i]] -= d[i]*q[i];
    }

    for (int i = 0; i < n; i++) {
        ac += acc[i];
        acc[i] = 0;
        printf("%I64d ", ac+v[i]);
    }
    printf("\n");
}
