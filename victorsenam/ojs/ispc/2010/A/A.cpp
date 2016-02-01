#include <bits/stdc++.h>

using namespace std;

const int N = 1007;

int n;
int a[N];

bool cmp (int a, int b)
{ return b < a; }

int main () {
    int t;
    scanf("%d", &t);
    printf("%d\n\n", t);
    while (t--) {
        scanf("%d", &n);

        for (int i = 0; i < n; i++)
            scanf("%d", a+i);

        sort(a, a+n);
        swap(a[0], a[n-1]);

        printf("%d\n", n);
        for (int i = 0; i < n; i++) {
            if (i)
                printf(" ");
            printf("%d", a[i]);
        }
        printf("\n\n");
    }
}
