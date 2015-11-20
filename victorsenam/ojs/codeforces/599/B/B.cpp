#include <bits/stdc++.h>

using namespace std;

const int N = 100008;

int n, m;
int f[N];
int b[N];
int s[N];

int main () {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++) {
        scanf("%d", f+i);
        
        if (s[f[i]] == 0)
            s[f[i]] = i+1;
        else
            s[f[i]] = -1;
    }

    bool un = 1;
    bool pos = 1;
    for (int i = 0; i < m; i++) {
        scanf("%d", b+i);

        if (s[b[i]] == 0) {
            pos = 0;
        } else if (s[b[i]] == -1) {
            un = 0;
        } else {
            b[i] = s[b[i]];
        }
    }

    if (!pos)
        printf("Impossible\n");
    else if (!un)
        printf("Ambiguity\n");
    else{
        printf("Possible\n");
        for (int i = 0; i < m; i++)
            printf("%d ", b[i]);
        printf("\n");
    }
}
