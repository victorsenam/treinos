#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;

const int N = 2e5 + 7;

char str[2][N];

bool comp (int k, int i, int j, int n) {
    for (int l = 0; l < n; l++) {
        if (str[k][i+l] != str[k][j+l])
            return str[k][i+l] < str[k][j+l];
    }
    return 1;
}

void swi (int k, int i, int j, int n) {
    for (int l = 0; l < n; l++)
        swap(str[k][i+l], str[k][j+l]);
}

void trans (int k, int i, int j) {
    int n = j - i;
    
    if (n & 1) return;
    
    trans(k, i, i + n/2);
    trans(k, i + n/2, i + n);

    if (!comp(k, i, i+n/2, n/2))
        swi(k, i, i+n/2, n/2);
}

int main () {
    scanf(" %s %s", str[0], str[1]);
    int n = strlen(str[0]);
    trans(0, 0, n);
    trans(1, 0, n);

    for (int i = 0; i < n; i++) {
        if (str[0][i] != str[1][i]) {
            printf("NO\n");
            return 0;
        }
    }
    printf("YES\n");
}
