#include <bits/stdc++.h>

using namespace std;

const int N = 100007;

int n, m;
int q, nx[N];
int p[N];
int w[N];
bool c[N];
int a[N], b[N];

int u[N];

bool cmp_ed (int i, int j) {
    if (w[i] == w[j])
        return c[i] > c[j];
    return w[i] < w[j];
}

void fail () {
    printf("-1\n");
    exit(0);
}

int main () {
    scanf("%d %d", &n, &m);
    
    for (int i = 0; i < m; i++) {
        p[i] = i;
        scanf("%d %d", w+i, c+i);
    }

    sort(p, p+m, cmp_ed);

    for (int i = 0; i < n; i++)
        nx[i] = i+2;
    q = 0;

    for (int i = 0; i < m; i++){ 
        int k = p[i];
        if (c[k]) {
            a[k] = q;
            b[k] = ++q;
        } else {
            int ls = upper_bound(nx, nx+n, nx[0]) - nx - 1;
            if (nx[ls] > q)
                fail();
            else {
                a[k] = ls;
                b[k] = nx[ls];
                nx[ls]++;
            }
        }
    }

    for (int i = 0; i < m; i++)
        printf("%d %d\n", a[i]+1, b[i]+1);
}
