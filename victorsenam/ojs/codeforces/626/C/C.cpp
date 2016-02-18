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

int n, m;


int main () {
    scanf("%d %d", &n, &m);
    
    int s = 2*n;
    int t = 3*m;

    int att = 6;
    while (att <= min(s, t)) {
        if (max(s+2, t) <= max(s, t+3))
            s += 2;
        else
            t += 3;
        att += 6;
    }

    printf("%d\n", max(s, t));
}
