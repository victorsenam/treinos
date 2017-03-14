#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define lld I64d
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 10;
const int L = 4;
const bool H = 1;

char str[N][L+2];
int ts;

int main () {

    scanf("%d", &ts);

    for (int cs = 1; cs <= ts; cs++) {
        for (int i = 0; i < N; i++)
            scanf(" %s", str[i]);

        bool ok = 0;
        int i, j, k;

        if (H) {
            for (k = 1; !ok && k <= L; k++) {
                for (i = 0; !ok && i < N; i++) {
                    for (j = 0; !ok && j < N; j++) {
                        if (i == j) continue;
                        ok = 1;
                        for (int s = 0; ok && s < k; s++)
                            ok = (str[i][L-k+s] == str[j][s]);
                    }
                }
            }
        } else {
            printf("AA");
        }

        i--; j--; k--;
        
        assert(ok);

        for (int a = 0; a < N; a++) {
            if (a == j) continue;
            if (a == i || a == j) {
                printf("%s", str[i]);
                printf("%s", str[j]+k);
                for (int s = 0; s < k-1; s++)
                    printf("A");
            } else {
                printf("%s", str[a]);
            }
        }
        printf("\n");
    }
}
