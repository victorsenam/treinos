#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define debug(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 1e3+7;

int n;
int v[N];

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);

        int a= 0 ;
        for (int j = 0; j < i; j++)
            if (!v[j] || v[i]%v[j] == 0)
                a++;
        printf("%d\n", a);
        fflush(stdout);
    }
}
