#include <bits/stdc++.h>

using namespace std;

const int N = 100007;

bool cmp_s (int i, int j) {
    return i%10 < j%10;
}

int a[N];
int n, k;
int rat;

int main () {
    scanf("%d %d", &n, &k);

    for (int i = 0; i < n; i++)
        scanf("%d", a+i);

    sort(a, a+n, cmp_s);

    int can = 0;

    for (int i = n-1; i >= 0 && k; i--) {
        if (a[i] == 100)
            continue;
        int aux = min(k, 10-(a[i]%10));
        a[i] += aux;
        k -= aux;
        can += 100-a[i];
    }

    rat = 0;
    for (int i = 0; i < n; i++)
        rat += a[i]/10;
    rat += min(can, k)/10;

    printf("%d\n", rat);
}
