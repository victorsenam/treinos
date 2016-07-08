#include <bits/stdc++.h>

typedef long long int ll;

using namespace std;

const int N = 1007;
const int M = 2*N;

int n, m;
int hd[2][N], to[M], nx[M], es;
int qu[N], qi, qf;
int deg[2][N];
int cnt[N];
ll v[N];
int q, a;
bitset<N> msk[N], wrk[N];

int main () {
    while (scanf("%d %d", &n, &m) != EOF && (n || m)) {
        es = 2;
        qi = qf = 0;
        for (int i = 0; i < n; i++) {
            msk[i] = 0;
            wrk[i] = 0;
            deg[1][i] = 0;
            cnt[i] = 0;
            hd[0][i] = hd[1][i] = 0;
        }
        for (int i = 0; i < n; i++) {
            scanf("%lld %d %d", &v[i], &deg[0][i], &q);

            for (int j = 0; j < deg[0][i]; j++) {
                scanf("%d", &a);
                a--;

                nx[es] = hd[0][i]; to[es] = a; hd[0][i] = es++;
                nx[es] = hd[1][a]; to[es] = i; hd[1][a] = es++;
                deg[1][a]++;
            }
                
            if (!deg[0][i]) {
                qu[qf++] = i;
            }

            for (int j = 0; j < q; j++) {
                scanf("%d", &a);
                a--;

                wrk[i].set(a);
            }
        }

        while (qi < qf) {
            int u = qu[qi++];

            for (int ed = hd[1][u]; ed; ed = nx[ed]) {
                v[to[ed]] += v[u];
                cnt[to[ed]]++;

                if (cnt[to[ed]] == deg[0][to[ed]])
                    qu[qf++] = to[ed];
            }
        }

        qi = qf = 0;
        for (int i = 0; i < n; i++) {
            if (!deg[1][i])
                qu[qf++] = i;
            cnt[i] = 0;
        }

        while (qi < qf) {
            int u = qu[qi++];

            for (int ed = hd[0][u]; ed; ed = nx[ed]) {
                msk[to[ed]] |= (wrk[u] | msk[u]);

                cnt[to[ed]]++;
                if (cnt[to[ed]] == deg[1][to[ed]])
                    qu[qf++] = to[ed];
            }
        }

        printf("*****\n");
        for (int t = 0; t < m; t++) {
            ll res = 0;
            for (int i = 0; i < n; i++)
                if (wrk[i].test(t) && !msk[i].test(t))
                    res += v[i];
            printf("%d %lld\n", t+1, res);
        }
    }
}

