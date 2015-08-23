#include <bits/stdc++.h>

using namespace std;
typedef int num;
#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#else
#define debug(...) //
#endif

#define N 5005

int n;
bool ok;
pair<int, int> v[N];
int maxi;

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        scanf("%d %d", &(v[i].first), &(v[i].second));

    sort(v, v+n);

    maxi = v[n-1].second;
    ok = 1;
    for (int i = n - 1; i >= 0 && ok; i--) {
        if (maxi >= v[i].first)
            maxi = v[i].first;
        else if (maxi >= v[i].second)
            maxi = v[i].second;
        else
            ok = 0;
    }

    if (ok)
        printf("%d\n", v[n-1].second);
    else
        printf("%d\n", v[n-1].first);
}
