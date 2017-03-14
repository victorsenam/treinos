#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%d| ", __LINE__); fprintf(stderr, __VA_ARGS__)
#else
#define debug(...) //
#endif

#define N 6000

using namespace std;

typedef int num;

int n;
int a, b;
int f[N];

int main () {
    scanf("%d", &n);
    for (int i = 0; i < N; i++) f[i] = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &a);
        f[a-1]++;
    }

    a = 0;
    b = 0;
    for (int i = 0; i < N/2; i++) {
        if (f[i] <= 1) continue;
        b = max(b, i);
        while (f[b]) b++;
        f[i]--;
        f[b]++;
        a += b-i;

        i--;
    }

    printf("%d\n", a);
}
