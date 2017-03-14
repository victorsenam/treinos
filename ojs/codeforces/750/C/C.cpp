#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;

const int N = 2e5+7;

int a;
int r;
int n;
int d[N], c[N]; 
int s;

void fail () {
    printf("Impossible\n");
    exit(0);
}

int main () {
    scanf("%d", &n);

    s = 0;
    r = 5e7;
    a = 0;

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &c[i], &d[i]);

        if (d[i] == 2) {
            s = 1;

            r = min(r, 1899-a);
        }

        a += c[i];
    }

    if (s == 0) {
        printf("Infinity\n");
        return 0;
    }

    a = 0;
    for (int i = 0; i < n; i++) {
        if (d[i] == 2 && r+a >= 1900)
            fail();
        else if (d[i] == 1 && r+a < 1900)           
            fail();
        a += c[i];
    }

    printf("%d\n", r+a);
}

