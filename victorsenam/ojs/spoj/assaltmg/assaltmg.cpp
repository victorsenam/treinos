#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <climits>

using namespace std;

unsigned int dir[21];
int mini, m, d, t;

void btrack (int i, unsigned int mask, int seq) {
    int keys;

    if (i >= d) return;

    keys = __builtin_popcount(mask | dir[i]);

    if (keys >= m) {
        if (seq+1 < mini) mini = seq+1;
    } else {
        btrack(i+1, mask, seq);
        btrack(i+1, (mask | dir[i]), seq+1);
    }
}

int main () {
    int n, aux;

    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &m, &d);
        mini = INT_MAX;

        for (int i = 0; i < d; i++) {
            scanf("%d", &n);
            dir[i] = 0;
            for (int j = 0; j < n; j++) {
                scanf("%d", &aux);
                dir[i] |= 1u << aux;
            }
        }

        btrack(0, 0u, 0);

        if (mini == INT_MAX) printf("Desastre!\n");
        else printf("%d\n", mini);
    }
}
