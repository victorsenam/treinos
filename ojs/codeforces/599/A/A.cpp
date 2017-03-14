#include <bits/stdc++.h>

using namespace std;

int a, b, c;
int ans;

int main () {
    scanf("%d %d %d", &a, &b, &c);    

    ans = a+b+c;
    ans = min(ans, a+a+b+b);
    ans = min(ans, a+a+c+c);
    ans = min(ans, b+b+c+c);

    printf("%d\n", ans);
}
