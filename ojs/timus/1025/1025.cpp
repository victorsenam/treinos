#include <algorithm>
#include <cstdio>

using namespace std;

const int N = 102;

int n;
int res;
int a[N];

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        scanf("%d", a+i);

    sort(a, a+n);

    for (int i = 0; i < (n+1)/2; i++)
        res += (a[i]+1)/2;

    printf("%d\n", res);
}
