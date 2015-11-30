#include <bits/stdc++.h>

using namespace std;

int main ( ){
    int n, m;
    int a, b, c, d;

    scanf("%d %d %d %d %d %d", &n, &m, &a, &b, &c, &d);

    n = abs(a-c);
    m = abs(b-d);

    if (n+m > 6)
        printf("Second\n");
    else
        printf("First\n");
}
