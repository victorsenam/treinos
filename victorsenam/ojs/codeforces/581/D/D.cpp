#include <bits/stdc++.h>

using namespace std;

const int N = 101;

int x[3], y[3];
int w[3], h[3];
int p[3];
int ar;
int siz;

void fail() {
    printf("-1\n");
    exit(0);
}

void suc() {
    printf("%d\n", siz);
    for (int i = 0; i < h[0]; i++) {
        for (int j = 0; j < siz; j++) {
            if (j < w[0])
                printf("%c", 'A'+p[0]);
            else
                printf("%c", 'A'+p[1]);
        }
        printf("\n");
    }
    for (int i = h[0]; i < siz; i++) {
        for (int j = 0; j < siz; j++)
            printf("%c", 'A'+p[2]);
        printf("\n");
    }
}

int main () {
    ar = 0;
    for (int i = 0 ; i < 3; i++) {
        scanf("%d %d", x+i, y+i);
        ar += x[i]*y[i];
        if (x[i] < y[i])
            swap(x[i], y[i]);
        p[i] = i;
    }

    siz = sqrt(ar);
    if (ar != siz*siz)
        fail();

    for (int i = 0; i < 3; i++)
        if (x[i] > siz)
            fail();

    bool aleq = 1;
    for (int i = 0; i < 3; i++)
        if (x[i] != siz)
            aleq = 0;

    if (aleq) {
        printf("%d\n", siz);
        for (int i = 0; i < 3; i++) {
            for (int k = 0; k < y[i]; k++) {
                for (int j = 0; j < siz; j++)
                    printf("%c", 'A'+i);
                printf("\n");
            }
        }
        return 0;
    }

    do {
        for (int mask = 0; mask < (1<<3); mask++) {
            for (int i = 0; i < 3; i++) {
                w[i] = x[p[i]];
                h[i] = y[p[i]];
                if (mask&(1<<i))
                    swap(w[i], h[i]);
            }

            if (w[0] + w[1] != siz)
                continue;
            if (h[0] != h[1])
                continue;
            if (w[2] != siz)
                continue;
            if (h[2] + h[1] != siz)
                continue;

            suc();
            return 0;
        }
    } while (next_permutation(p, p+3));

    fail();
}
