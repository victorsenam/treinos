#include <bits/stdc++.h>

using namespace std;

const int N = 100007;

typedef unsigned long long int num;

struct di {
    num qtd;
    bool val;
};

di v[N];
num tot[2];
num sum[2];
int t, n;
num res;
char c;
num a;

int main () {
    scanf("%d", &t);

    while (t--) {
        scanf("%d", &n);

        tot[0] = tot[1] = sum[0] = sum[1] = res = 0;
        for (int i = 0; i < n; i++) {
            scanf("%llu %c", &a, &c);
            v[i].val = (c == 'W');
            v[i].qtd = a;
            tot[v[i].val] += v[i].qtd;
        }
        if (tot[0] == 0) {
            printf("%llu\n", tot[1]);
            continue;
        } else if (tot[1] == 0) {
            printf("%llu\n", tot[0]);
            continue;
        }
        
        for (int i = 0; i < n; i++) {
            bool ty = v[i].val;

            if (sum[!ty]*tot[ty] % tot[!ty] == 0) {
                num k = sum[!ty]*tot[ty]/tot[!ty] - sum[ty];
                if (k > 0 && k <= v[i].qtd)
                    res++;
            }

            sum[ty] += v[i].qtd;
        }

        printf("%llu\n", res);
    }
}
