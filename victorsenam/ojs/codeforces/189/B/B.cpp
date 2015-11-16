#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long int num;

int main () {
    num w, h;
    scanf("%I64u %I64u", &w, &h);

    num ans = 0llu;
    w++;h++;
    
    num i = 2llu;
    while (w > i && h > i) {
        ans += (w-i)*(h-i);
        i += 2llu;
    }
    printf("%I64u\n", ans);
}
