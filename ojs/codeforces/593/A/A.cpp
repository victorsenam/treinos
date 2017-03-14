#include <bits/stdc++.h>

using namespace std;

const int N = 107;
const int S = 1007;

int n;
char str[S];
char has[N][2];
int siz[N];

int main () {
    scanf("%d", &n);

    int val = 0;
    for (int i = 0; i < n; i++) {
        scanf(" %s", str);

        has[i][0] = str[0];
        has[i][1] = 0;

        bool ok = 1;
        for (siz[i] = 1; ok && str[siz[i]]; siz[i]++) {
            if (has[i][0] == str[siz[i]])
                continue;
            else if (has[i][1] == 0)
                has[i][1] = str[siz[i]];
            else if (has[i][1] != str[siz[i]])
                ok = 0;
        }

        if (!ok)
            siz[i] = 0;

    }

    int maxi = 0;
    for (int i = 'a'; i <= 'z'; i++) {
        for (int j = 'a'; j <= 'z'; j++) {
            int loc = 0;

            for (int k = 0; k < n; k++) {
                if (has[k][0] && has[k][0] != i && has[k][0] != j)
                    continue;
                if (has[k][1] && has[k][1] != i && has[k][1] != j)
                    continue;
                loc += siz[k];
            }

            maxi = max(maxi, loc);
        }
    }
    printf("%d\n", maxi);
}
