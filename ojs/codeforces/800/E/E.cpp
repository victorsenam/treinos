#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define debug(...) {}
#endif

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 1e3+7;

int v[N];
int mat[N][N];
int anc;
int n;

int query (int x, int y) {
    if (mat[x][y] != -1)
        return mat[x][y];
        
}

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        v[i] = i;

    
}
