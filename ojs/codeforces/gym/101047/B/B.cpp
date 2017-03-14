#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 40;

int str[N], ss;
int n, ts;

int main () {
    scanf("%d", &ts);

    while (ts--) {
        scanf("%d", &n);

        bool one = 0;
        for (int b = 2; b <= 16; b++) {
            int aux = n;
            ss = 0;
            while (aux) {
                str[ss++] = aux%b;
                aux /= b;
            }
            bool ok = 1;
            for (int i = 0; i < ss; i++)
                ok &= (str[i] == str[ss-1-i]);

            one |= ok;
            if (ok)
                printf("%d ", b);
        }
        if (!one)
            printf("-1");
        printf("\n");
    }
}
