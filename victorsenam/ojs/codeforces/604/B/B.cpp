#include <bits/stdc++.h>

using namespace std;

typedef int num;

const int N = 100007;

int n, k;
num s[N];

int main () {
    scanf("%d %d", &n, &k);

    for (int i = 0 ; i < n; i++)
        scanf("%d", s+i);

    if (k >= n) {
        printf("%d\n", s[n-1]);
        return 0;
    }
    
    int maxi = 0;

    while (n < 2*k) {
        maxi = max(s[--n], maxi);
        k--;
    }

    for (int i = 0; i < k; i++) {
        maxi = max(s[i]+s[n-i-1], maxi);
    }

    printf("%d\n", maxi);
}
