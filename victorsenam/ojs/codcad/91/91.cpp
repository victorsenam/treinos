#include <bits/stdc++.h>

int h, p, f, d;

int main () {
    scanf("%d %d %d %d", &h, &p, &f, &d);

    p = (p - h + 16)%16;
    f = (f - h + 16)%16;

    if ((p > f)^(d == 1))
        printf("S\n");
    else
        printf("N\n");
}
