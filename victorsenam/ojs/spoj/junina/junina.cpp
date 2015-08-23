#include <bits/stdc++.h>

using namespace std;

unsigned int pro, mems[21];
int m, maxi, aux, bits;

void btrack (int i, unsigned int mem, unsigned int mask, int esc) {
    if (i < m) {
        if (!((mem|(1u<<i)) & (mask|mems[i])) && esc+1 > maxi) maxi = esc+1;

        btrack(i+1, mem, mask, esc);
        btrack(i+1, mem|(1u<<i), mask|mems[i], esc+1);
    }
}

int main () {
    int t = 0;
    while (scanf("%d", &m) != EOF && m) {
        t++;
        for (int i = 0; i < m; i++) {
            mems[i] = 0;
            while (scanf("%d", &aux) != EOF && aux) {
                mems[i] |= 1u<<(aux-1);
            }
        }

        maxi = 0;

        btrack(0, 0u, 0u, 0);

        printf("Teste %d\n%d\n\n", t, maxi);
    }
}
