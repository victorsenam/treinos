#include <bits/stdc++.h>

using namespace std;

#define UP (((1<<8)-1)<<8)

int m[UP+1][4];
int t, b, v;

void printbin (int v) {
    for (int i = 0; i < 16; i++) {
        printf("%d", v%2);
        v /= 2;
    }
}

int pd (int s, int l) {
    if (l>3) return 4;
    if (m[s][l] >= 0) return m[s][l];

    m[s][l] = 4;

    for (int i = 0; i < 16; i++) {
        if (!(s&(1<<i))) continue;
        for (int j = 0; j < 16; j++) {
            if (s&(1<<j)) continue;

            if (i/4 == j/4) {
                if ((i%4) + (j%4) == 3) continue;
            } else if (i/4 + j/4 == 3) continue;
            else if (i%4 != j%4) continue;
            
            m[s][l] = min(m[s][l], pd(s-(1<<i)+(1<<j), l+1) + 1);
        }
    }

 //   printbin(s);
 //   printf(" %d -> %d\n", l, m[s][l]);
    return m[s][l];
}

int main () {
    scanf("%d", &t);
    
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < UP; i++) {
            m[i][j] = -1;
        }
        m[UP][j] = 0;
    }


    for (int c = 0; c < t; c++) {
        v = 0;
        for (int i = 0; i < 16; i++) {
            scanf("%d", &b);
            if (b) v += (1<<i);
        }

        pd(v, 0);
        printf("Case #%d: ", c+1);
        if (m[v][0] >= 4) printf("more\n");
        else printf("%d\n", m[v][0]);
    }
}
