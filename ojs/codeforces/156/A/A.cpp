#include <bits/stdc++.h>

using namespace std;

const int N = 2007;

char a[N], b[N];
int maxi;
int n, m;
int pa[N], pb[N];

bool comp_a (int i, int j) {
    return (strcmp(a+i, a+j) < 0);
}

bool comp_b (int i, int j) {
    return (strcmp(b+i, b+j) < 0);
}

int main () {
    scanf(" %s %s", a, b);
    n = strlen(a);
    m = strlen(b);
    
    maxi = 0;
    for (int i = 0; i < n; i++) {
        int k = 0;
        int r = 0;

        while (i + k < n && k < m) {
            if (a[i+k] == b[k])
                r++;
            k++;
        }
        maxi = max(maxi, r);
    }

    for (int i = 0; i < m; i++) {
        int k = 0;
        int r = 0;

        while (i + k < m && k < n) {
            if (b[i+k] == a[k])
                r++;
            k++;
        }
        maxi = max(maxi, r);
    }

    printf("%d\n", m-maxi);
}
