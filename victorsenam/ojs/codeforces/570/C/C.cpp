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

#define N 300007

int n, m;
char str[N];
int a;
char c;
set<int> s;
set<int>::iterator ct, at, dt;

int main () {
    scanf("%d %d", &n, &m);

    scanf(" %s", str);

    s.insert(0);
    s.insert(n+1);
    int last = 0;
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (str[i-1] != '.') {
            ans += max(0, i - last - 2);
            last = i;
            s.insert(i);
        }
    }
    ans += max(0, n+1-last-2);
    
    for (int i = 0; i < m; i++) {
        scanf("%d %c", &a, &c);

        ct = s.lower_bound(a);
        at = ct;
        at--;
        dt = ct;
        dt++;

        if (c == '.') {
            if (*ct == a) {
                ans -= max(*ct-*at-2, 0);
                ans -= max(*dt-*ct-2, 0);
                ans += max(*dt-*at-2, 0);
                s.erase(a);
            }
        } else {
            if (*ct != a) {
                dt = ct;
                ans -= max(*dt-*at-2, 0);
                ans += max(*dt-a-2, 0);
                ans += max(a-*at-2, 0);
                s.insert(a);
            }
        }
        printf("%d\n", ans);
    }
}
