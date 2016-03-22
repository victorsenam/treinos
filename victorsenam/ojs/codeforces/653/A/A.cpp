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

const int N = 1007;

int n;
int t[N];

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int a;
        scanf("%d", &a);
        t[a]++;
    }

    for (int i = 2; i < 1007; i++) {
        if (t[i] && t[i-1] && t[i-2]) {
            printf("YES\n");
            return 0;
        }
    }

    printf("NO\n");
}
