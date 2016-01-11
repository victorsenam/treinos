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

const int N = 1000007;

char a[N], b[N];
int sa, sb;
int ia, ib;

int main () {
    scanf(" %s %s", a, b);

    ia = ib = 0;
    while (a[ia] && a[ia] == '0')
        ia++;
    while (b[ib] && b[ib] == '0')
        ib++;

    sa = strlen(a+ia);
    sb = strlen(b+ib);

    if (sa > sb)
        printf(">\n");
    else if (sb > sa)
        printf("<\n");
    else {
        for (int i = 0; i < sa; i++) {
            if (a[i+ia] == b[i+ib])
                continue;
            else if (a[i+ia] > b[i+ib])
                printf(">\n");
            else
                printf("<\n");
            return 0;
        }

        printf("=\n");
    }
}
