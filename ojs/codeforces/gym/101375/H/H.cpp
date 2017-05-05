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
ll lo, hi, mid;
char c;

int main () {
    lo = 1;
    hi = 1e9;

    while (lo <= hi) {
        mid = (lo+hi)/2;

        printf("Q %lld\n", mid);
        fflush(stdout);

        scanf(" %c", &c);

        if (c == '=')
            return 0;
        else if (c == '<')
            hi = mid - 1;
        else
            lo = mid + 1;
    }
}
