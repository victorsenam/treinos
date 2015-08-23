#include <bits/stdc++.h>

using namespace std;

const int N = 54;
const int T = 207;
const int inf = 100000;

struct state {
    int est, tem, dir;
};

int memo[N][T];
int tr[N][T][2];
int n, m, s, b;
int sum;
int a[N];
queue<state> q;
state aux;

int pd (int i, int t) {
    if (i == n-1 && t == s)
        return 0;
    if (i < 0 || i >= n || t > s)
        return inf;

    int & m = memo[i][t];
    if (m != -1) 
        return m;
    m = min(inf, pd(i, t+1)+1);
    if (i < n-1 && tr[i][t][0]) {
        m = min(m, pd(i+1, t+a[i+1]));
    }
    if (i > 0 && tr[i][t][1]) {
        m = min(m, pd(i-1, t+a[i]));
    }

    return m;
}

int main () {
    int c = 1;
    while (scanf("%d %d", &n, &s) != EOF && n) {
        a[0] = 0;
        sum = 0;

        memset(memo, -1, sizeof(memo));
        memset(tr, 0, sizeof(tr));

        for (int i = 1; i < n; i++) {
            scanf("%d", a+i);
            sum += a[i];
        }

        scanf("%d", &m);
        for (int i = 0; i < m; i++) {
            scanf("%d", &b);
            aux.tem = b;
            aux.est = 0;
            aux.dir = 0;
            q.push(aux);
        }

        scanf("%d", &m);
        for (int i = 0; i < m; i++) {
            scanf("%d", &b);
            aux.tem = b;
            aux.est = n-1;
            aux.dir = 1;
            q.push(aux);
        }

        while (!q.empty()) {
            aux = q.front();
            q.pop();

            if (aux.tem > s || tr[aux.est][aux.tem][aux.dir])
                continue;
            else {
                tr[aux.est][aux.tem][aux.dir] = 1;
                aux.est += 1 - 2*aux.dir;
                if (aux.est < 0 || aux.est >= n) continue;
                aux.tem += a[aux.est + aux.dir];
                q.push(aux);
            }
        }

        int ans = pd(0,0);
        printf("Case Number %d: ", c++);
        if (ans >= inf) printf("impossible\n");
        else printf("%d\n", ans);
    }
}   
