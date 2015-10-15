#include <bits/stdc++.h>

using namespace std;

int main () {
    printf("1\n");
    printf("%d\n", 26*26);
    for (char i = 'a'; i <= 'z'; i++){
        for (char j = 'a'; j <= 'z'; j++) {
            printf("%c%c\n", i,j);
        }
    }
}
