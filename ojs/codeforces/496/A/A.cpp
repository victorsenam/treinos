#include <bits/stdc++.h>

/**/

using namespace std;

const int N = 103;

int a[N];
int n;

int main () {
    scanf("%d", &n);
    int maxi = 0;
    int mini = INT_MAX;
    for (int i =0 ; i < n; i++) {
        scanf("%d", a+i);
        if (i) {
            maxi = max(maxi, a[i] - a[i-1]);
        }
        if (i > 1) {
            mini = min(mini, a[i] - a[i-2]);
        }
    }
    
    printf("%d\n", max(maxi, mini));
}
