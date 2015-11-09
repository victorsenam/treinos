#include <bits/stdc++.h>

using namespace std;

typedef int num;

const int N = 4002;

int n, k;
char str[N][N];
int acc[N][N];

int main () {
    scanf("%d %d", &n, &k);

    for (int i = 0; i < n; i++) {
        scanf(" %[0-9 ]", &str[i]);
        for (int j = 0; j < n; j++)
            str[i][j] = str[i][(j<<1)]-'0';
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d", str[i][j]);
        printf("\n");
    }

    
}
