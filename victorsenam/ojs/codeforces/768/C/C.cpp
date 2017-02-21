#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = (1<<10);

int n, k, x;
int v;
int qt[2][N];

int main () {
    scanf("%d %d %d", &n, &k, &x);

    for (int i = 0; i < n; i++) {
        scanf("%d", &v);
        qt[!(k&1)][v]++;
    }

    bool t = 0;
    while (k--) {
        t = 0;
        for (int i = 0; i < N; i++) {
            if (!qt[k&1][i])
                continue;


            if (!t) {
                qt[k&1][i]--;
                qt[!(k&1)][i^x]++;
                t = 1;
            }

            qt[!(k&1)][i^x] += qt[k&1][i]/2;
            qt[!(k&1)][i] += (qt[k&1][i]+1)/2;
            
            if (qt[k&1][i]%2)
                t = 0;
            qt[k&1][i] = 0;
        }
    }

    int mn = 0;
    int mx = N-1;
    while (!qt[1][mn])
        mn++;
    while (!qt[1][mx])
        mx--;

    printf("%d %d\n", mx, mn);
}
