#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define debug(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 2e5+7;

bool ok[N];
int c;
int v[N];
int n;

int main () {
    scanf("%d %d", &c, &n);

    for (int i = 0; i < n; i++)
        scanf("%d", &v[i]);

    sort(v, v+n);    

    int l = 1;

    for (int i = 0; i < n; i++) {
        while (l < v[i]) {
                
        }
    }
}
