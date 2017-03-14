#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef int num;
#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#else
#define debug(...) //
#endif

#define N 1002

int n;
int v[N];
int d;

int main () {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", v+i);

    d = (n - v[0])%n;

    for (int i = 0; i < n; i++) {
        v[i] += n;
        if (i%2) v[i] -= d;
        else v[i] += d;
        v[i] %= n;

        if (v[i] != i) {
            printf("No\n");
            return 0;
        }
    }
    printf("Yes\n");
}
