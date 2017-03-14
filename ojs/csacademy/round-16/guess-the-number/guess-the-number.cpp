#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define debug(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 10;
char v[N];
int cr = 0;
char t = '9';

int main () {
    scanf("%d", &n);
    
    while (cr < n) {
        v[cr] = 0;
(       printf("Q %s", v);
        for (int i = cr; i < n; i++)
            putchar(t);
        putchar('\n');
        fflush(stdout);

        int nw;
        scanf("%d", &nw);

        for (int i = cr; i < nw; i++)
            v[i] = t;

        t--;
    }
}
