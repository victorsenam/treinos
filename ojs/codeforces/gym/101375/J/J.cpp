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

int n, m;
int a;
char c;

int main () {
    scanf("%d %d", &n, &m);

    int la = -10;
    char lc = 'S';

    for (int i = 0; i < m; i++) {
        scanf("%d %c", &a, &c);
        if (c == 'M' || (c != lc && a - la < 4)) {
            printf("No\n");
            return 0;
        }
        
        la = a;
        lc = c;
    }
    printf("Yes\n");
}
