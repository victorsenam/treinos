#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define debug(...) {}
#endif

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 2e5+7;

int n;
int c[N];
int a[N], b[N];
int f[N];

int p[3][N], ps[3], at[3];

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        scanf("%d", &c[i]);

    for (int i = 0;i <n; i++) {
        scanf("%d", &a[i]);
        a[i]--;
    }
    for (int i = 0;i <n; i++) {
        scanf("%d", &b[i]);
        b[i]--;
    }

    for (int j = 0; j < 3; j++) {
        for (int i = 0; i < n; i++) {
            if (a[i] == j || b[i] == j) {
                p[j][ps[j]++] = i;
            }
        }
        sort(p[j], p[j]+ps[j], [] (int i, int j) { return c[i] < c[j]; });
    }
    

    int m = 0;
    scanf("%d", &m);

    for (int i = 0; i < m; i++) {
        int j;
        scanf("%d", &j);
        j--;
        int rs = 0;

        while (at[j] < ps[j] && f[p[j][at[j]]]) at[j]++;
        if (at[j] == ps[j]) {
            rs = -1;
        } else {
            rs = c[p[j][at[j]]];
            f[p[j][at[j]]] = 1;
        }

        printf("%d ", rs);
    }
    printf("\n");
}

