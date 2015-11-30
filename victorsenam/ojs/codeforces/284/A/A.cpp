#include <bits/stdc++.h>

using namespace std;

int p;
int ans;

int main () {
    ans = 0;

    scanf("%d", &p);

    for (int i = 1; i < p; i++) {
        int x = i;
        int j = 2;
        for (j = 1; j < p-1; j++) {
            if (x == 1)
                break;
            x = (x*i)%p;
        }
        if (j < p-1)
            continue;

        if (x == 1)
            ans++;
    }
    printf("%d\n", ans);
}
