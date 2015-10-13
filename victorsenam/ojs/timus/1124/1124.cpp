// WA
#include <bits/stdc++.h>

using namespace std;

const int N = 51;
const int M = 501;

int m, n;
int hd[M], nx[N*M], to[N*M], es;
int a;

int main () {
    memset(hd, -1, sizeof hd);
    scanf("%d %d", &m, &n);

    int res = 0;

    for (int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            scanf("%d", &a);
            a--;
            if (a == i)
                continue;
            nx[es] = hd[i]; hd[i] = es; to[es] = a; es++;
        }
    }

    int att = -1;
    for (int i = 0; i < m; i++) {
        while (hd[i] != -1) {
            if (att != -1 && att != i)
                res++;
            att = i;
            while (hd[att] != -1) {
                int go = to[hd[att]];
                hd[att] = nx[hd[att]];
                //printf("%d -> %d\n", att, go);
                att = go;
                res++;
            }
        }
    }
    printf("%d\n", res);
}
