#include <bits/stdc++.h>

using namespace std;

int n, m;
int att, a;

int main () {
    scanf("%d %d", &m, &n);

    att = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &a);

        att = max(0, att+a-m);
    }
    printf("%d\n", att);
    
}
