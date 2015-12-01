#include <bits/stdc++.h>

using namespace std;

int main ( ){
    int n = 400;

    int m = 0;

    printf("%d\n", 19900);

    for (int i = 1; i <= n/2; i++) {
        for (int j = i+1; j <= n/2; j++) {
            printf("%d %d\n", i, j);
        }
    }
}
