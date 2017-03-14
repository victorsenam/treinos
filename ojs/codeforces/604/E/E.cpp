#include <bits/stdc++.h>

using namespace std;

int n, k;
int ans;
int a;

int calc (int i) {
    if (i < 4)
        return (i&1);
    if (i == 4)
        return 2;
    if (i&1)
        return 0;

    if (calc(i/2) != 1)
        return 1;
    else
        return 2;
}

int main ( ){ 
    scanf("%d %d", &n, &k);

    ans = 0;

    for (int i = 0; i < n; i++) {
        scanf("%d", &a);

        if (a == 0) {
            continue;
        } else if (a == 1) {
            ans ^= 1;
        } else if (a == 2) {
            if (k&1)
                continue;
            else
                ans ^= 2;
        } else if (a == 3) {
            if (k&1)
                ans ^= 1;
            else
                continue;
        } else if (a&1) {
            continue;
        } else {
            if (k&1) {
                ans ^= calc(a);
            } else {
                ans ^= 1;
            }
        }
    }

    if (ans)
        printf("Kevin\n");
    else
        printf("Nicky\n");
}
