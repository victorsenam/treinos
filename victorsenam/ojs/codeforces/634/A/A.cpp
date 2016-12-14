#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define debug(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 2e6+7;

int a[2][N];
int n;
int s[2];

int main () {
    
    scanf("%d", &n);
    

    for (int j = 0; j < 2; j++) {
        for (int i = 0; i < n; i++) {
            scanf("%d", &a[j][i]);
            if (a[j][i] == 1)
                s[j] = i;
        }
    }

    int mat = 0;
    while (mat < n) {
        for (int j = 0; j < 2; j++) {
            s[j] = (s[j]+1)%n;
            while (a[j][s[j]] == 0) s[j] = (s[j]+1)%n;
        }

        if (a[0][s[0]] != a[1][s[1]]) break;
        mat++;
    }
    if (mat == n)
        printf("YES\n");
    else
        printf("NO\n");
}
