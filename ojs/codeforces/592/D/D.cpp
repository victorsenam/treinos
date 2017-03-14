#include <bits/stdc++.h>

using namespace std;

const int N = 200007;
const int M = 2*N;

bool bad[N], ex[N];
int hd[N], nx[M], to[M], es;
int q[N], qi, qf;
int dg[N];
int n, m;
int a, b;
bool visi[M][2];
int memo[M][3];

int solve (int eg, bool vol) {
    int u;
    int & me = (eg<0)?memo[-eg][2]:memo[eg][vol];
    if (eg < 0) {
        u = -eg-1;
    } else {
        u = to[eg];
        if (visi[eg][vol])
            return me;
        visi[eg][vol] = 1;
    }

    int sum = 0;
    for (int ed = hd[u]; ed != -1; ed = nx[ed]) {
        if ((ed^1) == eg)
            continue;
        if (ex[to[ed]])
            continue;
        sum += solve(ed, 1) + 2;
    }

    me = sum;

    if (!vol) {
        for (int ed = hd[u]; ed != -1; ed = nx[ed]) {
            if ((ed^1) == eg)
                continue;
            if (ex[to[ed]])
                continue;
            me = min(me, sum-solve(ed, 1)+solve(ed,0)-1);
        }
    }
    
    return me;
}

int main () {
    scanf("%d %d", &n, &m);
    memset(hd, -1, sizeof hd);


    for (int i = 1; i < n; i++) {
        scanf("%d %d", &a, &b);
        a--; b--;

        nx[es] = hd[a]; hd[a] = es; to[es] = b; es++;
        nx[es] = hd[b]; hd[b] = es; to[es] = a; es++;
        dg[a]++;
        dg[b]++;
    }

    int cb = 0;
    for (int i = 0; i < m; i++) {
        scanf("%d", &a);
        a--;
        bad[a] = 1;
        cb++;
    }

    qi = qf = 0;
    for (int i = 0; i < n; i++) {
        if (dg[i] == 1)
            q[qf++] = i;
    }

    while (qi < qf) {
        int u = q[qi++];
        if (bad[u])
            continue;
        ex[u] = 1;
        for (int ed = hd[u]; ed != -1; ed = nx[ed]) {
            dg[to[ed]]--;
            if (dg[to[ed]] == 1)
                q[qf++] = to[ed];
        }
    }

    int mini = INT_MAX;
    int best = 0;
    for (int i = 0; i < n; i++) {
        if (ex[i]) continue;
        int loc = solve(-i-1, 0);
        if (loc < mini) {
            mini = loc;
            best = i;
        }
    }
    printf("%d\n%d\n", best+1, mini);
}
