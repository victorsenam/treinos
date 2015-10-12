#include <bits/stdc++.h>

using namespace std;

const int N = 4003;

int fr, sr;
int v, d, p;
int n;
int res[N], ss;
int st[N], dw;

int main () {
    scanf("%d", &n);

    fr = sr = ss = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &v, &d, &p);

        if (fr + sr > p) {
            fr -= dw;
            sr += d;
        } else {
            fr -= dw;
            fr += v;
            dw++;
            if (i+v < n)
                st[i+v]++;
            res[ss++] = i;   
        }
        dw -= st[i];
        //printf("%d %d\n", fr, sr);
    }

    printf("%d\n", ss);
    for (int i = 0; i < ss; i++) {
        if (i) printf(" ");
        printf("%d", res[i]+1);
    }
}
