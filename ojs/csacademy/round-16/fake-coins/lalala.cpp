#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define debug(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 1e3+7;

int p[N];
int pv;
int res[2];
int n;

vector<int> v[3];

void ans () {
    printf("A %d %d\n", res[0], res[1]);
    fflush(stdout);
    exit(0);
}

int query (int s) {
    int d = 0;

    printf("%d %d", s, s);
    for (int i = 0; i < s; i++) {
        if (i > a.size())
            printf(" %d", v[2][d++]);
        else
            printf(" %d", v[0][i]);
    }
    for (int i = 0; i < s; i++) {
        if (i > b.size())
            printf(" %d", v[2][d++]);
        else
            printf(" %d", v[1][i]);
    }
    fflush(stdout);

    int r;
    scanf("%d", &r);
    return r;
}

int main () {
    scanf("%d", &n);

    int pt = (1<<(__builtin_popcount(n)-1));
    for (int i = 1; i <= pt/2; i++)
        v[0].push_back(i);
    for (int i = pt/2 + 1; i <= pt; i++)
        v[1].push_back(i);
    for (int i = pt+1; i <= n; i++)
        v[2].push_back(i);
    
       
    :w

}
