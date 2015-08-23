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

#define N 51

char tab[N][N];
int n, m;
bool cont[256];
int cnt;

int main () {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf(" %c", &tab[i][j]);
        }
    }

    cnt = 0;
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < m-1; j++) {
            cont['a'] = cont['c'] = cont['e'] = cont['f'] = 0;
            for (int k = 0; k < 3; k++)
                cont[tab[i + k/2][j + k%2]] = 1;
            cont[tab[i+1][j+1]] = 1;

            if (cont['a'] && cont['c'] && cont['e'] && cont['f'])
                cnt++;
        }
    }

    printf("%d\n", cnt);
}
