#include <bits/stdc++.h>

using namespace std;

int a, i, f;
char c;
int n;

int main() {
    scanf("%d", &n);

    for (int j = 0 ;j < n; j++) {
        scanf(" %c", &c);
        if (c == 'A')
            a++;
        else if (c == 'I')
            i++;
        else
            f++;
    }

    if (i == 1)
        printf("%d\n", 1);
    else if (i > 1)
        printf("0\n");
    else
        printf("%d\n", a);
}
