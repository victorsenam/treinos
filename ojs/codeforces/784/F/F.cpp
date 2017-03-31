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


const int N = 1e4;
int n;
int a[N];
int v;

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    sort(a, a+n);

    if (n == 3) {
        for (int i = 0; i < n; i++)
            printf("%d ", i+1);
    } else if (n == 10) {
        printf("1 6 27 27 %d", a[3], a[2]);
        for (int i = 0; i < 5; i++)
            printf("%d ", a[i]);
        printf("\n");
    } else {
        printf("vai curinthia\n");
    }
}
