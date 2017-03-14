#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif


int ts, n;
int main () {
    scanf("%d", &ts);

    while (ts--) {
        scanf("%d", &n);

        for (int i = 0; i < n; i++)
            printf("%c", 'a'+(i%26));
        printf("\n");
    }
}
