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

int n;
int v[4];

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int a = 0;
        scanf("%d", &a);
        v[i%4] += a;
    }

    int mx = 0;
    for (int i = 0; i < 4; i++)
        mx = max(mx, v[i]);
    for (int i = 0; i < 4; i++)
        if (mx == v[i]) {
            printf("%c\n", 'A'+i);
            return 0;
        }
}
