#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 6e4+7;
const int M = 1e4+7;

int t;
int n, m, q;
int uf[N], wf[N];
int a[N], b[N], c[N], p[N];

bool cmp_t (int i, int j) {
    if (c[i] != c[j])
        return c[i] < c[j];
    return i < j;
}

int find (int i) {
    if (i == uf[i]) return i;
    return uf[i] = find(uf[i]);
}

bool join (int i, int j) {
    if ((i = find(i)) == (j = find(j))) return 0;
    if (wf[i] > wf[j]) swap(i, j);
    wf[j] += wf[i];
    uf[i] = j;
    return 1;
}

int main () {
    scanf("%d", &t);

    while (t--) {
        scanf("%d %d %d", &n, &m, &q);
        for (int i = 0; i < m + q; i++) {
            scanf("%d %d %d", a+i, b+i, c+i);
            a[i]--; b[i]--;
            p[i] = i;
        }

        sort(p, p+m+q, cmp_t);

        for (int k = m; k < m+q; k++) {
            for (int i = 0; i < n; i++) {
                wf[i] = 1;
                uf[i] = i;
            }

            int sum = 0;
            for (int _i = 0; _i < m+q; _i++) {
                int i = p[_i];
                if (i > k) continue;
                if (join(a[i],b[i]))
                    sum += c[i];
            }
            printf("%d\n", sum);
        }
    }
}
