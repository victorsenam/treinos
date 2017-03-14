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

#define N 1000007

int n;
bool v[N];
int res, att, ini;
char c;
int a;

int main () {
    scanf("%d", &n);

    res = 0;
    att = 0;
    ini = 0;

    for (int i = 0; i < n; i++) {
        scanf(" %c %d", &c, &a);
        
        if (v[a]) {
            v[a] = 0;
            att--;
        } else {
            if (c == '-') {
                att--;
                ini++;
            } else {
                att++;
                v[a] = 1;
            }
        }

        res = max(att, res);
    }
    printf("%d\n", res+ini);
}
