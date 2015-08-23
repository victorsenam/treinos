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

int n, k, a, m, p;
int qtd;
set<int> s;
set<int>::iterator it, jt;

int main () {
    scanf("%d %d %d %d", &n, &k, &a, &m);

    qtd = (n+1)/(a+1);

    if (qtd < k) {
        printf("0\n");
        return 0;
    }

    s.insert(0);
    s.insert(n+1);

    for (int i = 0; i < m; i++) {
        scanf("%d", &p);
        jt = it = s.lower_bound(p);
        if (*it == p) continue;
        it--;

        qtd -= ((*jt) - (*it))/(a+1);
        qtd += ((*jt)-p)/(a+1) + (p-(*it))/(a+1);

        s.insert(p);

        if (qtd < k) {
            printf("%d\n", i+1);
            return 0;
        }
    }

    printf("-1\n");
}
