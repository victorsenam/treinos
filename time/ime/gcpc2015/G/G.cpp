#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef int num;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 2000;

int n;
int a;

int main () {
    scanf("%d", &n);
    int maxi = 0;

    for (int i = 0; i < n; i++) {
        scanf("%d", &a);
        if (a < maxi) {
            printf("no\n");
            return 0;
        }
        maxi = max(a, maxi);
    }
    printf("yes\n");
}
