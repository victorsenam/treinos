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

#define N 100004

int n;
int k;

int m[N];
set<int> s;
int a, b;
int res;

int main () {
    scanf("%d %d", &n, &k);

    res = 0;
    for (int i = 0; i < k; i++) {
        scanf("%d", m+i);
        res += 2*m[i];
        scanf("%d", &a);
        if (a == 1) {
            b = 1;
            for (int j = 1; j < m[i]; j++) {
                scanf("%d", &a);
                if (a == b+1) b++;
            }
            res -= 2*b;
        } else {
            for (int j = 1; j < m[i]; j++)
                scanf("%d", &a);
            res -= 1;
        }
    }

    printf("%d\n", res);
}
