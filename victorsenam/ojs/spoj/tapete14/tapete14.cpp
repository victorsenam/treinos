#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

ll l, n;

int main () {
    scanf("%lld %lld", &l, &n);

    printf("%lld\n", n - 1 + (l-n+1)*(l-n+1));
}
