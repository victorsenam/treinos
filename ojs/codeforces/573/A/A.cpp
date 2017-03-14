#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef int num;
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n");}
#else
#define debug(...) {}
#endif

#define N 

int n;
int a;
int res;

int main () {
    scanf("%d", &n);

    scanf("%d", &a);
    while (a%2 == 0)
        a /= 2;
    while (a%3 == 0)
        a /= 3;
    res = a;

    for (int i = 1; i < n; i++) {
        scanf("%d", &a);
        while (a%2 == 0)
            a /= 2;
        while (a%3 == 0)
            a /= 3;
        if (res != a) {
            printf("No\n");
            return 0;
        }
    }

    printf("Yes\n");
}
