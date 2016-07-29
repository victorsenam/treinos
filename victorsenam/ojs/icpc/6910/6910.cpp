#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 20007;

int uf[N], wf[N];
int pr[N];
int qs[N][2];
bool rm[N];
int ts;
int n, q;
int r[N], rs;

int find (int i) {
    if (uf[i] == i) return i;
    return uf[i] = find(uf[i]);
}

void join (int i, int j) {
    if ((i = find(i)) == (j = find(j))) return;
    if (wf[i] < wf[j]) swap(i, j);
    wf[i] += wf[j];
    uf[j] = i;
}

int main () {
    scanf("%d", &ts);
    for (int tc = 1; tc <= ts; tc++) {
        scanf("%d %d", &n, &q);

        for (int i = 0; i < n; i++) {
            scanf("%d", pr+i);
            pr[i]--;
            uf[i] = i;
            wf[i] = 1;
            rm[i] = 0;

            if (pr[i] == -1)
                pr[i] = i;
        }

        for (int i = 0; i < q; i++) {
            char c;
            scanf(" %c", &c);

            if (c == 'Q') {
                scanf("%d %d", &qs[i][0], &qs[i][1]);
                qs[i][0]--; qs[i][1]--;
            } else {
                scanf("%d", &qs[i][0]);
                qs[i][0]--;
                qs[i][1] = -1;

                if (rm[qs[i][0]]) qs[i][0] = -1;
                else rm[qs[i][0]] = 1;
            }
        }

        for (int i = 0; i < n; i++)
            if (!rm[i])
                join(i, pr[i]);

        rs = 0;
        printf("Case #%d:\n", tc);
        for (int i = q-1; i >= 0; i--) {
            if (qs[i][1] == -1) {
                if (qs[i][0] != -1)
                    join(qs[i][0], pr[qs[i][0]]);
            } else {
                r[rs++] = (find(qs[i][0]) == find(qs[i][1]));
            }
        }

        for (int i = rs-1; i >= 0; i--)
            if (r[i])
                printf("YES\n");
            else
                printf("NO\n");
    }
}
