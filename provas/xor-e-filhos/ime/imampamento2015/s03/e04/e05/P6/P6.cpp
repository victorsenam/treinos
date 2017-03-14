#include <bits/stdc++.h>

using namespace std;

const int N = 14;
const int M = (1<<12)+12;
const int P = 5;
const int T = 320;

int n, ts;
int tim[P][N];
int memo[M][P][T];

int pd(int i, int p, int t) { 
    if (t <= 0) return 0;
    if (i == (1<<n)-1) return 0;
    
    int & m = memo[i][p][t];

    if (m != -1)
        return m;

    m = 0;
    for(int j = 0; j < 3; j++) {
        if (j == p) continue;
        for (int k = 0; k < n; k++) {
            if ((i&(1<<k)) == 0 && t-tim[j][k] >= 0) {
                m = max(pd((i|(1<<k)), j, t-tim[j][k])+1, m);
            }
        }
    }
    
    //printf("%d %d %d -> %d\n", i, p, t, m);
    return m;
}

int main () {
    scanf("%d", &ts);
    while (ts--) {
        scanf("%d", &n);
        for (int i = 0; i < (1<<n); i++)
            for (int p = 0; p <= 3; p++)
                for (int t = 0; t <= 300; t++)
                    memo[i][p][t] = -1;

        for (int i = 0; i < 3; i++) {
            for( int j = 0; j < n; j++) {
                scanf("%d", &tim[i][j]);
            }
        }

        printf("%d\n", pd(0, 3, 280));
    }   
}
