#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

int c;
int cn;
int n;
int ts;
int ls;

int main () {
    scanf("%d", &ts);

    while (ts--) {
        scanf("%d", &n);
        cn = 0;
        ls = -1;
        bool ok = 0;
        for (int i = 0;i < n; i++) {
            scanf("%d", &c);

            if (c != ls) {
                cn = 0;
                ls = c;
            }
                
            cn++;
            if (cn == 3)
                ok = 1;
        }

        if (ok)
            printf("Yes\n");
        else
            printf("No\n");
    }

}
