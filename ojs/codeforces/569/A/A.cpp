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


int t, s, q;

int main () {
    scanf("%d %d %d", &t, &s, &q);

    int res = 0;

    int down = s;
    while (down < t) {
        down += down*(q-1);
        res++;
    }



    printf("%d\n", res);
}
