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

int n, a;

int main () {
    scanf("%d", &n);
    int r=0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &a);
        r+=a;
    }
    printf("%d\n", (r+4)/5);

}
