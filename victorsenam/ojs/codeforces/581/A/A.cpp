#include <bits/stdc++.h>

using namespace std;


int a, b;

int main () {
    scanf("%d %d", &a, &b);

    printf("%d %d\n", min(a, b), (max(a,b)-min(a, b))/2);
}
