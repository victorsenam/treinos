#include <bits/stdc++.h>
using namespace std;
typedef int num;
const int MS = 20;
const int MN = 6e3;
char in[MN][MS];
int n, siz, aux, p[MN], ans;

bool strless(int i, int j)
{ return strcmp(in[i],in[j]) < 0; }

int main()
{
    freopen("names.txt", "r", stdin);
    while ( scanf(" %*[^A-Z]%[A-Za-z]", &in[n]) != EOF ) p[n] = n++;
    sort(p, p+n, strless);
    for(int k=0;k<n;k++)
    {
        int i = p[k];
        aux = 0;
        for(int j=0;in[i][j]!=0;j++)
            aux += in[i][j] - 'A' + 1;
        ans += aux*(k+1);
    }
    printf("%d\n", ans);
    fclose(stdin);
}
