#include <bits/stdc++.h>

using namespace std;

int ch;
int need;
int a[3], x[3];

int main () {
    scanf("%d %d %d", a, a+1, a+2);
    scanf("%d %d %d", x, x+1, x+2);


    for (int i = 0; i < 3; i++) {
        a[i] -= x[i];
        if (a[i] > 0)
            ch += (a[i]>>1);
        else if (a[i] < 0)
            need -= a[i];
    }

    if (need > ch)
        printf("No\n");
    else
        printf("Yes\n");
}
