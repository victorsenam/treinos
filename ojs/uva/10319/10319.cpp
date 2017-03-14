#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define lld I64d
#define DEBUG(...) {}
#endif

const int N = 1000;
const int M = 2000;

int m[2], n;
int q[2][2];
int hd[N], to[M], nx[M], es;
int ts;
int pre[N], ret[N], os;
int visi[N], turn;
int st[N], ss;
int comp[N], cs;

int dfs (int u) {
    if (visi[u] == turn)
        return pre[u];
    if (visi[u] == turn+1)
        return INT_MAX;
    visi[u] = turn;
    pre[u] = ret[u] = os++;
    st[ss++] = u;
    for (int ed = hd[u]; ed; ed = nx[ed])
        ret[u] = min(dfs(to[ed]), ret[u]);
    visi[u] = turn+1;

    if (pre[u] == ret[u]) {
        while (ss && pre[st[ss-1]] >= ret[u])
            comp[st[--ss]] = cs;
        cs++;
    }
    
    return ret[u];
}

void addor (int x, int y) {
    nx[es] = hd[x^1]; to[es] = y; hd[x^1] = es++;
    nx[es] = hd[y^1]; to[es] = x; hd[y^1] = es++;
}

int main () {
    scanf("%d", &ts);

    while (ts--) {
        turn += 2;
        scanf("%d %d %d", m, m+1, &n);

        es = 2;
        cs = ss = os = 0;
        memset(hd, 0, sizeof hd);
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < 2; k++) {
                for (int l = 0; l < 2; l++) {
                    scanf("%d", &q[k][l]);
                    q[k][l]--;
                    if (l)
                        q[k][l] += m[0];
                    q[k][l] *= 2;
                }
            }

            for (int l = 0; l < 2; l++)
                if (q[0][l] > q[1][l])
                    for (int k = 0; k < 2; k++)
                        q[k][!l]++;

            // se for necessario algum movimento naquele sentido, alguma das vias deve estar correta
            for (int l = 0; l < 2; l++)
                if (q[0][l] != q[1][l])
                    addor(q[0][!l], q[1][!l]);

            // tanto na entrada quanto na saida, pelo menos uma rua deve estar correta
            for (int k = 0; k < 2; k++)
                addor(q[k][0], q[k][1]);
        }

        //printf("%d + %d\n", m[0], m[1]);
        for (int i = 0; i < 2*(m[0]+m[1]); i++) {
            dfs(i);
            //printf("[%d]%d : %d\n", i%2, i/2, comp[i]);
        }

        bool ok = 1;
        for (int i = 0; i < 2*(m[0]+m[1]) && ok; i += 2) {
            ok = (comp[i] != comp[i+1]);
        }
        if (ok)
            printf("Yes\n");
        else
            printf("No\n");
    }
}
