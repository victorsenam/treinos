#include <bits/stdc++.h>

using namespace std;

typedef long long int num;

const int N = 10007;

int n, p[N];
num x[N], y[N];

bool cmp_ang (int i, int j)
{ return (x[p[0]]*y[i] + y[p[0]]*x[j] + x[i]*y[j] - y[i]*x[j] - y[j]*x[p[0]] - y[p[0]]*x[i]) < 0ll; }

int main ( ) {
    scanf("%d", &n);

    int mini = 0;
    for (int i = 0; i < n; i++) {
        scanf("%lld %lld", x + i, y + i);
        p[i] = i;
        if (x[i] < x[mini] || (x[i] == x[mini] && y[i] < y[mini]))
            mini = i;
    }

    swap(p[0], p[mini]);

    sort(p+1, p+n, cmp_ang);

    printf("%d %d\n", p[0]+1, p[n/2]+1);
}
