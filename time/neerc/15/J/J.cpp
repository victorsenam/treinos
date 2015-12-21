#include <bits/stdc++.h>
using namespace std;

const int N = 1007;

int n;
int a[N];
int eq[N];
int r;

int main () {
    srand(time(NULL)); rand(); rand();
    scanf(" %d", &n);
    
    do {
        for (int i = 0; i < n; i++) {
            a[i] = rand()%2;
            printf("%d", a[i]);
        }
        printf("\n");
    fflush(stdout);

        scanf(" %d", &r);
        if (r == n)
            return 0;
    } while (r+r != n);
    
    eq[0] = a[0];
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j || j == 0)
                printf("%d", !a[j]);
            else
                printf("%d", a[j]);
        }
        printf("\n");
    fflush(stdout);

        scanf(" %d", &r);
        if (r == n)
            return 0;
        else if (r+r == n)
            eq[i] = !a[i];
        else
            eq[i] = a[i];
    }

    for (int i = 0; i < n; i++)
        printf("%d", eq[i]);
    printf("\n");
    fflush(stdout);

    scanf(" %d", &r);
    if (r == n)
        return 0;

    for (int i = 0; i < n; i++)
        printf("%d", !eq[i]);
    printf("\n");
    fflush(stdout);
}
