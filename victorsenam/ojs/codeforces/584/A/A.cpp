#include <bits/stdc++.h>
using namespace std;

int n, t;

int main () {
    scanf("%d %d", &n, &t);

    if (n== 1 && t== 10)
        printf("-1\n");
    else {
        printf("%d", t);
        if (t == 10) n--;
        for (int i = 1; i < n; i++)
            printf("0");
        printf("\n");
    }
}
