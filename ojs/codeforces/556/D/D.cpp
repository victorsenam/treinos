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

#define N 200004

int n, m;
pair<int, int> isl[N];
pair<int, int> bri[N];
vector<int> adj[2*N+2];
int a;

int main () {
    scanf("%d %d", &n, &m);

    if (m < n-1) {
        printf("No\n");
        return 0;
    }

    for (int i = 0; i < n; i++)
        scanf("%d %d", &isl[i].first, &isl[i].second);
    
    for (int i = 0; i < m; i++) {
        scanf("%d", &bri[i].first);
        bri[i].second = i+1;
    }
    sort(bri.begin(), bri.end());
    
    
}
