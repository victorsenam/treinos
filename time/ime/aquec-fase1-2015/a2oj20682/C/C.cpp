#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long int num;

int t;
num n;
num m;
num x;

int main () {
    scanf("%d", &t);

    while (t--) {
        scanf("%llu", &x);

        m = ULLONG_MAX;
        for (n = 2llu; n*n < 2llu*x; n++) {
            if ((2llu*x)%n)
                continue;

            if ((2llu*x/n - n-1llu) % 2llu)
                continue;

            m = (2llu*x/n - n-1)/2llu;
            break;
        }


        if (n*n >= 2llu*x) {
            printf("IMPOSSIBLE\n");
            continue;
        }

        printf("%llu = ", x);
        for (num i = 1llu; i <= n; i++) {
            if (i > 1llu)
                printf(" + ");
            printf("%llu", i+m);
        }
        printf("\n");
    }
}
