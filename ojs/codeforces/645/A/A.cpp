#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef int num;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

char a[4], b[4];
char x[4];


int main () {
    for (int i = 0; i < 4; i++)
        scanf(" %c", a+i);
    for (int i = 0; i < 4; i++)
        scanf(" %c", b+i);

    swap(a[2], a[3]);
    swap(b[2], b[3]);

    for (int i = 0; i < 4; i++)
        x[i] = a[i];
    
    for (int i = 0; i < 4; i++) {
        if (a[i] == 'A') {
            for (int j = 0; j < 4; j++)
                a[j] = x[(i+j)%4];
            break;
        }
    }
    for (int i = 0; i < 4; i++)
        x[i] = b[i];
    for (int i = 0; i < 4; i++) {
        if (b[i] == 'A') {
            for (int j = 0; j < 4; j++)
                b[j] = x[(i+j)%4];
            break;
        }
    }

    int i = 1;
    if (a[i] == 'X') i++;
    int j = 1;
    if (b[j] == 'X') j++;

    if (a[i] == b[j])
        printf("YES\n");
    else
        printf("NO\n");
}
