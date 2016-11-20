#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define debug(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 28;

char str[N];
int fr[900];
int rep;
int p[3];

char mid[N];
int ms;
char res[N];
int rs;

int rev (int i, int j) {
    int mid = (i+j)/2;
    for (int k = i; k < mid; k++)
        swap(str[i], str[j]);
}

int main () {
    scanf(" %s", str);

    for (int i = 0; i < 27; i++) {
        if (fr[str[i]]) rep = i;
        fr[str[i]]++;
    }

    int k = 0;
    for (int i = 0; i < 27; i++) {
        if (str[i] == str[rep]) k++;
        else p[k]++;
    }

    if (p[1] == 0) {
        printf("Impossible\n");
        return 0;
    }
    
    rs = ms = 0;

    if (p[1]%2)
        mid[ms++] = str[rep];
    else
        res[rs++] = str[rep];

    for (int i = p[0]+1; i < p[0]+p[1]+1; i++)
        mid[ms++] = str[i];

    for (int i = p[0]+p[1]+2; i < 27; i++)
        res[rs++] = str[i];
    for (int i = 0; i < p[0]; i++)
        res[rs++] = str[i];

    for (int i = rs/2; i < rs; i++)
        putchar(res[i]);
    for (int i = 0; i < ms/2; i++)
        putchar(mid[i]);
    putchar('\n');
    for (int i = rs/2-1; i >= 0; i--)
        putchar(res[i]);
    for (int i = ms-1; i >= ms/2; i--)
        putchar(mid[i]);
    putchar('\n');

}
