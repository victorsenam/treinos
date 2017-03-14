#include <bits/stdc++.h>

using namespace std;
typedef int num;
#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#else
#define debug(...) //
#endif


#define N 1002

int n, k;
char str[N];

int main () {
    scanf(" %s %d", str, &k);

    for (n = 0; str[n] != '\0'; n++);
    if (n%k) {
        printf("NO\n");
        return 0;
    }

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < n/(2*k); j++) {
            if (str[i*n/k + j] != str[i*n/k + n/k - 1 - j]) {
                printf("NO\n");
                return 0;
            }
        }
    }

    printf("YES\n");
}
