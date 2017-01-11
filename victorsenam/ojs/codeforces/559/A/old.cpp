#include <bits/stdc++.h>

using namespace std;

typedef long long int num;

num res;
int a[7];

int main () {
    for (int i = 0; i < 6; i++)
        scanf("%d", a+i);

    sort(a, a+6);

    while (a[5]) {
        int cnt = 0;
        int s = 0;
        for (int i = 0; i < 6; i++) {
            s += a[i]+a[i]-1;

            if (a[i]) {
                a[i]--;
                cnt++;
            }
        }

        if (cnt == 3) {
            if (s == 3) {
                res++;
            } else {
                res += 3;
                for (int i = 0; i < 3; i++)
                    a[i]--;
                for (int i = 3; i < 6; i++)
                    a[i] = 1;
            }
            continue;
        }

        res += s;
    }
    printf("%I64d\n", res);
}
