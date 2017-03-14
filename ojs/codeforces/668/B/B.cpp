#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 1000007;

int n, q;
ll s[2];
bool t, d;
int kind;
int x;
int p[N];

int main () {
    scanf("%d %d", &n, &q);
    t= 1;

    for (int i = 0; i < q; i++) {
        scanf("%d", &kind);
        if (kind == 1) {
            scanf("%d", &x);
            for (int k = 0; k <2; k++) {
                s[k] += x;
            }
            if (x%2)
                t = !t;
        } else {
            s[t]++;
            s[!t]--;
            t = !t;
        }
    }
    for (int i = 0; i < n; i++) {
        p[((i+s[!(i%2)])%n+n)%n] = i;
    }
    for (int i = 0; i < n; i++)
        printf("%d ", p[i]+1);
    printf("\n");
}
