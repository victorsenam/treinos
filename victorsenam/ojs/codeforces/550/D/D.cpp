#include <bits/stdc++.h>

using namespace std;
typedef int num;
#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#else
#define debug(...) //
#endif


#define N 

int k;

int main () {
    scanf("%d", &k);
    if (k%2==0) {
        printf("NO\n");
        return 0 ;
    }

    printf("YES\n");
    printf("%d %d\n", 4*(k-1)+2, (2*(k-1)+1)*k );

    printf("%d %d\n", 4*(k-1)+1, 4*(k-1)+2);
    for (int i = 0; i < k-1; i++) {
        for (int j = k-1; j < 2*(k-1); j++)
            printf("%d %d\n", i+1, j+1);
        printf("%d %d\n", i+1, 4*(k-1)+1);
    }

    for (int i = 2*(k-1); i < 3*(k-1); i++) {
        for (int j = 3*(k-1); j < 4*(k-1); j++)
            printf("%d %d\n", i+1, j+1);
        printf("%d %d\n", i+1, 4*(k-1)+2);
    }

    for (int i = k-1; i < 2*(k-1); i++) {
        if (i%2) continue;
        printf("%d %d\n", i+1, i+2);
    }

    for (int i = 3*(k-1); i < 4*(k-1); i++) {
        if (i%2) continue;
        printf("%d %d\n", i+1, i+2);
    }
}
