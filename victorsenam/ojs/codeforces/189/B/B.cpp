#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long int num;

int main () {
    num w, h;
    scanf("%I64u %I64u", &w, &h);

    num ans = 0llu;
    
    for (num i = 2; i <= w; i+=2)
        for (num j = 2; j <= h; j+=2) {
            ans += (w-i+1llu)*(h-j+1llu);
        }

    printf("%I64u\n", ans);
}
