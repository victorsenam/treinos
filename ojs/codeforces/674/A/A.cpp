#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 5007;

int n;
int v[N], c[N], r[N];

int main () {
    scanf("%d", &n);
    for( int i =0 ; i < n; i++) {
        scanf("%d", v+i);
        v[i]--;
    }

    for (int i = 0; i < n; i++) {
        pair<int, int> maxi(0,0);
        for (int j = 0; j < n; j++) {
            c[j] = 0;
        }

        for (int j = i; j < n; j++) {
            c[v[j]]++;
            if (pair<int, int>(c[v[j]], -v[j]) > maxi)
                maxi = pair<int, int>(c[v[j]], -v[j]);

            r[-maxi.second]++;
        }
    }

    for (int i = 0; i  < n; i++)
        printf("%d ", r[i]);
    printf("\n");
}
