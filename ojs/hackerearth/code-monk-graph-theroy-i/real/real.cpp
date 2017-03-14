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

#define N 10000

int e;
int t;
int a;
set<int> s;

int main () {
    scanf("%d", &t);
    while (t--) {
        s.clear();

        scanf("%d", &e);
        for (int i = 0; i < 2*e; i++) {
            scanf("%d", &a);
            s.insert(a);
        }

        printf("%d\n", s.size());
    }
}
