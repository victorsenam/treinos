#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;

int n;
int p;
int a;
char d[30];

void fail () {
    printf("NO\n");
    exit(0);
}

int main () {
    scanf("%d", &n);

    p = 0;

    for (int i = 0; i < n; i++) {
        scanf("%d %s", &a, d);

        if (p == 0 && d[0] != 'S')
            fail();
        if (p == 20000 && d[0] != 'N')
            fail();

        if (d[0] == 'N')
            p -= a;
        else if (d[0] == 'S')
            p += a;

        if (p < 0 || p > 20000) {
            fail();
        }
    }

    if (p != 0)
        fail();
    printf("YES\n");
}
