#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef int num;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n");}
#else
#define DEBUG(...) {}
#endif

set<int> s;
int n, m;

int main () {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++) {
        int q;
        scanf("%d", &q);

        int a;
        for (int j = 0; j < q; j++) {
            scanf("%d", &a);
            s.insert(a);
        }
    }

    if (s.size() == m)
        printf("YES\n");
    else
        printf("NO\n");

}
