#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

int n, m;
int a[4];

int main () {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < 4; i++)
        scanf("%d", a+i);

    if (m < n+1 || n <= 4) {
        printf("-1\n");
        return 0;
    }

    for (int g = 0; g < 2; g++) {
        printf("%d %d ", a[0+2*g], a[2-2*g]);
        int k = 1;
        for (int i = 2; i < n-2; i++) {
            while (true) {
                int j = 0;
                for (j = 0; j< 4 && a[j] != k; j++);
                if (j == 4) break;
                k++;
            }
            printf("%d ", k++);
        }
        printf("%d %d\n", a[3-2*g], a[1+2*g]);
    }
}
