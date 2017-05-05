
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

int t, a, b;

int main () {
    scanf("%d", &t);

    while (t--) {
        scanf("%d %d", &a, &b);
        if (a > b) swap(a, b);

        if (a == (a+b)/2 && b == (a+b+1)/2)
            printf("Ok\n");
        else
            printf("%d %d\n", (a+b)/2, (a+b+1)/2);
    }
}
