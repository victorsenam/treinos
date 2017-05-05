#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define debug(...) {}
#endif

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back


const int N = 5e3+7;
const int M = 3e7;

int l, n[4];
int v[4][N];
int w[2][M];
int q[2];

int main () {
    while (scanf("%d", &l) != EOF && l) {
        for (int i = 0; i < 4; i++)
            scanf("%d", &n[i]);

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < n[i]; j++)
                scanf("%d", &v[i][j]);
        }

        for (int k = 0; k < 4; k+=2) {
            q[k/2] = 0;
            for (int i = 0; i < n[k]; i++)
                for (int j = 0; j < n[k+1]; j++)
                    if (v[k][i] + v[k+1][j] <= l) {
                        w[k/2][q[k/2]++] = v[k][i] + v[k+1][j];
                    }

        }

        sort(w[0], w[0] + q[0]);

        ll r = 0;
        for (int i = 0; i < q[1]; i++) {
            int x = upper_bound(w[0], w[0]+q[0], l - w[1][i]) - w[0];
            //printf("%d -> %d\n", w[1][i], x);
            r += x;
        }
            
        printf("%lld\n", r);
    }
}
