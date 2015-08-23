#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef int num;
#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#else
#define debug(...) //
#endif

ll c[3];

int main () {
    scanf("%d %d %d", c, c+1, c+2);
    sort(c, c+3);

    if (c[2] >= 2*(c[0]+c[1])) 
        printf("%d\n", c[0]+c[1]);
    else
        printf("%d\n", (c[0]+c[1]+c[2])/3);
}
