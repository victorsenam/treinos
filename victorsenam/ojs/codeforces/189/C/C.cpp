#include <bits/stdc++.h>

using namespace std;

const int N = 5000000;

int n;
int a[N], b[N];
bool u[N];
int ai, af;

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        scanf("%d", a+i);
    for (int i = 0; i < n; i++)
        scanf("%d", b+i);
        
    ai = 0;
    af = n;
    int j = 0;
    int ch = 0;

    while (ai < af) {
        if (a[ai] == b[j]) {
            ai++;
            j++;
        } else if (u[b[j]]) {
            j++;
        } else {
            u[a[--af]] = 1;
            ch++;
        }
    }

    printf("%d\n", ch);
}
