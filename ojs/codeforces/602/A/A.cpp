#include<bits/stdc++.h>

using namespace std;

typedef long long int num;

int n, b;
num va, vb;
num in[20];
num pot;

int main () {
    scanf("%d %d", &n, &b);

    for (int i = n-1; i >= 0; i--)
        scanf("%d", in+i);

    pot = 1;
    va = 0;
    for (int i = 0; i < n; i++) {
        va += pot*in[i];
        pot *= b;
    }

    scanf("%d %d", &n, &b);
    for (int i = n-1; i>= 0; i--)
        scanf("%d", in+i);
    pot = 1;
    vb = 0;
    for (int i = 0; i < n; i++) {
        vb += pot*in[i];
        pot *= b;
    }

    if (va > vb)
        printf(">\n");
    else if (va == vb)
        printf("=\n");
    else
        printf("<\n");
}
