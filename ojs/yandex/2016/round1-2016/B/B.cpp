#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

char mat[3][3];
char res[3][3];
const int ord[8][2] = {
    {0, 0}, {0, 1}, {0, 2}, {1, 2}, {2, 2}, {2, 1}, {2, 0}, {1, 0}
};

int main () {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            scanf(" %c", &mat[i][j]);
    res[1][1] = '1';

    int ch = -1;
    bool rev = 0;
    for (int i = 0; i < 8; i++) {
        int l = ord[i][0];
        int c = ord[i][1];
        if (mat[l][c] == '?') continue;

        if (ch == -1)
            ch = (8+mat[l][c]-'2'-i)%8;
        else if (mat[l][c]-'2' != (8-i+ch)%8)
            rev = 1;
    }

    for (int i = 0; i < 8; i++) {
        int a = i;
        if (rev) a = (8-i)%8;

        int l = ord[a][0];
        int c = ord[a][1];

        res[l][c] = (8-i+ch)%8+'2';
    }

    for (int i = 0; i <3; i++) {
        for (int j = 0; j < 3; j++) 
            putchar(res[i][j]);
        putchar('\n');
    }
}
