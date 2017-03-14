#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;

const int N = 2e5;

int main () {
    printf("%d %d %d\n", N, N, 1);
    for (int i = 1; i < N; i++)
        printf("%d %d 1\n", i, i+1);
    printf("%d %d 1\n", N, 1);
}
