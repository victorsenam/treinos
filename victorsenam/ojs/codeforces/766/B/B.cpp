#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 1e5+7;

int n;
int a[N];

int main () {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    sort(a, a+n);


    for (int i = 2; i < n; i++)
        if (a[i-2] + a[i-1] > a[i]) {
            printf("YES\n");
            return 0;
        }
    printf("NO\n");
}
