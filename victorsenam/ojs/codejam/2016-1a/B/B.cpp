#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 10;
const int M = 2507;

int ts, t;
int n;
int a;
int fr[M];

int main () {
    scanf("%d", &ts);
    for (t = 1; t <= ts; t++) {
        scanf("%d", &n);
        memset(fr, 0, sizeof fr);
        for (int i = 0; i < 2*n-1; i++) {
            for (int j = 0; j < n; j++) {
                scanf("%d", &a);
                fr[a]++;
            }
        }
        
        printf("Case #%d:", t);
        for (int i = 0; i < M; i++) {
            if (fr[i]&1)
                printf(" %d", i);
        }
        printf("\n");
    }
}
