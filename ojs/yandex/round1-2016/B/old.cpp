#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

int ord[8] = {7, 0, 1, 6, 2, 5, 4, 3};

char mat[8];
int k;
int fnd[2];

int main () {
    bool rev = 0;
    int p0 = 0;
    for (int i = 0; i < 8; i++) {
        scanf("%c", &mat[ord[i]]);
        if (mat[ord[i]] == '1' || mat[ord[i]] == '\n')
            i--;
        else if (mat[ord[i]] != '?') {
            fnd[k++] = mat[ord[i]];
            if (k == 0)
                p0 = ord[i];
            else
                rev = !((8+ord[i]-p0)%8==(8+fnd[1]-fnd[0])%8);
        }
    }
    if (rev) {
        for (int i = 0; i < 8; i++)
            ord[i] = (8-ord[i])%8;
        for (int i = 1; i < 8-i; i++)
            swap(mat[i], mat[8-i]);
    }
    
    int ch = -1;
    for (int i = 0; i < 8; i++) {
        if (mat[i] == fnd[0]) {
            int p = fnd[0]-'0'-2;
            ch = 8-i+p;
        }
    }
    bool ok = 0;
    int kk = 0;
    for (int i = 0; i < 8; i++, kk++) {
        if (!ok && i == 4) {
            putchar('1');
            ok = 1;
            i--;
        } else {
            putchar('2'+(ord[i]+ch)%8);
            if (kk%3 == 2)
                putchar('\n');
        }
    }
}
