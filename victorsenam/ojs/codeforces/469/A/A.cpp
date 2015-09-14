#include <bits/stdc++.h>


using namespace std;

const int N = 107;

int n, v[N], p, a;
int res;

int main () {
    scanf("%d", &n);
    
    for (int k = 0; k < 2; k++) {
        scanf("%d", &p);
        for (int i = 0; i < p; i++) {
            scanf("%d", &a);
            if (!v[a])
                res++;
            v[a] = 1;
        }
    }

    if (res >= n)
        printf("I become the guy.\n");
    else
        printf("Oh, my keyboard!\n");
}
