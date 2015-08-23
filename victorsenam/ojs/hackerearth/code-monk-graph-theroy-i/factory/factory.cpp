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

#define N 

int n;
int g;
int a;

int main () {
    scanf("%d", &n);
    g = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &a);
        g += a;
    }

    if (2*n == g+2) printf("Yes\n");
    else printf("No\n");
}
