#include <bits/stdc++.h>

using namespace std;

const int N = 103;

char str[N];
char a[N];
int car;
int zer;

int main () {
    scanf(" %s", str);
    for (zer = 0; str[zer] != '\0'; zer++);
    for (int i = 0; i < zer; i++)
        a[N-i-1] = str[zer-i-1]-'0';

    while (scanf(" %s", str) != EOF) {
        for (zer = 0; str[zer] != '\0'; zer++);

        car = 0;
        for (int i = 0; i < zer || car; i++) {
            if (i < zer)
                a[N-i-1] += str[zer-i-1] - '0';
            a[N-i-1] += car;
            car = a[N-i-1]/10;
            a[N-i-1] %= 10;
        }
    }

    zer = 0;
    for (int i = 0; i < N; i++)
        if (a[N-i-1]) zer = i;
    zer++;
    
    for (int i = 0; i < zer; i++)
        printf("%d", a[N-zer+i]);
    printf("\n");
}
