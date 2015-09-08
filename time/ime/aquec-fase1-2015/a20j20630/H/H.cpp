#include <bits/stdc++.h>

using namespace std;


const int S = 12;
const int N = 18;

int m;
int sol[N][2];
int vs[N][2];
int memo[N][S][2][S];
int vis[N][S][2][S];
int turn;
char seq[S][S];
int tam[S];
char val[N];
int t, ss, n;
int pot[N];

int solve(int q, bool l);

int pd(int q, int s, bool l, int c) {
    if (q + c >= tam[s])
        return 0;

    int & me = memo[q][s][l][c];

    if (vis[q][s][l][c] == turn)
        return me;
    vis[q][s][l][c] = turn;
    me = 0;

    if (c == tam[s])
        return me = pot[q] - solve(q, l);

    for (int i = 0; i < 10; i++) {
        if (!free && val[n-1-q] < i)
            break;

        if (seq[s][c] == i)
            me = pd(q-1, s, l||(i<val[n-1-q]), c+1);
        else
            me = pd(q-1, s, l||(i<val[n-1-q]), 0);
    }
    return me;
}

int solve(int q, bool l) {
    if (vs[q][l] == turn)
        return sol[q][l];

    int & se = sol[q][l];
    se = 0;
    
    for (int i = 0; i < ss; i++)
        se += pd(n, i, 0, 0);
    return se;
}

int main () { 
    scanf("%d", &t);

    pot[0] = 1;
    for (int i = 1; i < N; i++)
        pot[i] = pot[i-1]*10;

    while (t--) {
        scanf("%d", &ss);
        for (int i = 0; i < ss; i++) {
            scanf(" %s", seq[i]);
            tam[i] = strlen(seq[i]);
            for (int j = 0; j < tam[i]; j++)
                seq[i][j] -= '0';
        }
        scanf("%d", &m);
        for (int i = 0; i < m; i++) {
            turn++;
            scanf(" %s", val);
            n = strlen(val);
            for (int j = 0; j < n; j++)
                val[j] -= '0';
            printf("%d\n", solve(n, 0));
        }
    }
}
