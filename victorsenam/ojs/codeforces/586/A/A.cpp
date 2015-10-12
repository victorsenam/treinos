#include <bits/stdc++.h>

using namespace std;

bool last;
int sum;
int a;
int n;
int zr;

int main () {
    last =  0;
    scanf("%d", &n);
    
    zr = 2;
    for (int i = 0; i < n; i++) {
        scanf("%d", &a);
        
        if (a) {
            sum++;
            if (last == 0 && zr == 1)
                sum++;
        } else {
            if (last != 0)
                zr = 1;
            else
                zr++;
        }

        last = a;
    }
    printf("%d\n", sum);
}
