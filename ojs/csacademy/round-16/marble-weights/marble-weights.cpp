#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define debug(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 1e3+7;

int v[N];
int n;
int fs;

int r;

int main () {
    scanf("%d", &n);

    printf("Q 2 1 2\n");
    fflush(stdout);
    scanf("%d", &fs);

    printf("Q 3 1 2 3\n");
    fflush(stdout);
    scanf("%d", &r);
    v[3] = r - fs;

    printf("Q 2 2 3\n");
    fflush(stdout);
    scanf("%d", &r);

    v[2] = r - v[3];
    v[1] = fs - v[2];

    for (int i = 4; i <= n; i++) {
        printf("Q 2 %d %d\n", i-1, i);
        fflush(stdout);
        scanf("%d", &r);
        v[i] = r - v[i-1];
    }
    
    printf("A");
    for (int i = 1; i <= n; i++)
        printf(" %d", v[i]);
    printf("\n");
    fflush(stdout);
}
