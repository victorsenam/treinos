#include <bits/stdc++.h>

using namespace std;

int n, a, p;
int mini;
int res;

int main () {
    scanf("%d", &n);
    
    mini = INT_MAX;
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &a, &p);
        mini = min(p, mini);
        res += a*mini;
    }
    printf("%d\n", res);
}
