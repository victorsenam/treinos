#include <bits/stdc++.h>

using namespace std;

int main () {
    int n, k;
    scanf("%d %d", &n, &k);
    printf("%d %d\n", n, k);

    for (int i = 0; i < n; i++) {
        printf("%d ", rand()%2000000000-1000000000);
    }
}
