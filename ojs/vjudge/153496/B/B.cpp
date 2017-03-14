#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 60;
const int M = N*N;

int memo[M][N];
int visi[M][N], turn;
int v[N];
int n, ts;

int pd (int i, int x) {
    if (x > n*(n-1)/2)
        return M*M;
    if (i == n)
        return M*M*(x != n*(n-1)/2);
    
    int & me = memo[x][i];
    if (visi[x][i] == turn)
        return me;
    visi[x][i] = turn;

    me = M*M;
    for (int j = 0; j < n; j++)
        me = min(me, pd(i+1, x+j) + abs(v[i] - j));
    return me;
}

int main () {
    scanf("%d", &ts);
    while (ts--) {
        turn++;
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%d", &v[i]);
        printf("%d\n", pd(0, 0));
    }
}
