#include <bits/stdc++.h>

using namespace std;

typedef long long int num;

const int N = 25007;
const int C = 257;

char str[N];
num last[C];
num qtd[C];
num sum[C];
num ord[C];
num t;
num n;

bool cmp (int i, int j) {
    return last[i] < last[j];
}

int main () {
    scanf("%lld", &t);
    while (t--) {
        scanf("%lld", &n);

        scanf(" %s", str);

        memset(last, 0, sizeof last);
        memset(qtd, 0, sizeof qtd);
        memset(sum, 0, sizeof sum);

        for (int i = 0; i < n; i++) {
            last[str[i]] = max(last[str[i]], 1ll*i);
            sum[str[i]] += i+1;
            qtd[str[i]]++;
        }
        
        num pre = 0;
        num esp = 0;
        for (int i = 0; i < n; i++) {
            esp++;
            if (last[str[i]] == i)
                pre += esp*qtd[str[i]];
        }

        num pos = 0;
        esp = 0;
        for (int i = 0; i < n; i++) {
            if (last[str[i]] == i) {
                esp += qtd[str[i]];
                pos += esp*qtd[str[i]];
            }
        }

        printf("%lld\n", 5ll*(pre-pos));
    }

}
