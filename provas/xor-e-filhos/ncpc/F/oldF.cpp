#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 100;

int n;
int t, m;
int a, b;

void fail () {
    printf("impossible\n");
    exit(0);
}

int main ( ){
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &t, &m);

        int p = 0;
        for (int j = 0; j < m; j++) {
            scanf("%d %d", &a, &b);
            
            b -= a;

            if (b >= p && b >= t-p)
                fail();
            else if (b >= p)
                p += b;
            else if (b >= t-p)
                p -= b;
        }
    }

    printf("possible\n");
}

