#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef int num;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 200007;

int x[N];
int n;

int main () {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", x+i);

    int lo = 0;
    int hi = (x<<1)-1;

}
