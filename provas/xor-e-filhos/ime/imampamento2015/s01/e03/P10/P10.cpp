#include <bits/stdc++.h>

using namespace std;

int a, b;

int count (int val, int dig) {
    int i = 1;
    if (val != 0 && val%10 == 0)
        val--;
    int res = 0;
    int ans;
    for (i = 1; val/i != 0; i *= 10) res += (val/i)%10 == dig;
    i--;

    if (i > 1) 
        ans = count(val%i, dig)*((val/i)+1) + count(val/i, dig);
    else
        ans = (dig <= val);  
    
    if (val != 0 && val%10 == 0)
        return ans + res;
    else 
        return ans;
}

int main () {
    while (scanf("%d %d", &a, &b) != EOF && a && b) {
        printf("%d %d: ", a, b);
        for (int i = 0; i < 10; i++) {
            if (i) printf(" ");
            printf("%d", count(b,i)-count(a-1,i));
            printf("(%d,%d)", count(b,i), count(a-1,i));
        }
        printf("\n");        
    }
}
