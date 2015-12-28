#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef ll num;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n");}
#else
#define DEBUG(...) {}
#endif

const int N = 200007;

int hd[N], nx[N], to[N], es;
int n, qs;
int t[N], u[N];
num v[N];
num iv;

struct seg {
    int n;
};

int main () {
    scanf("%lld %d", &iv, &qs);

    hd[n++] = -1;
    for (int i = 0; i < qs; i++) {
        scanf("%d %d", t+i, u+i);
        if (t[i] == 1) {
            scanf("%lld", v+i);
            
        }
    }
}
