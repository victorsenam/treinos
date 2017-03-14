#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long int num;

const int N = 120;

int n, len;
char str[N];
num fin;
int st[N], ss;

bool bt (int i, num mask) {
    if (i == len)
        return (mask == fin);

    if (str[i] == '0')
        return 0;

    st[ss++] = i;

    int in = (str[i]-'1');
    for (int lp = 0; lp < 1+(i+1<len); lp++, in = (str[i]-'0')*10+(str[i+1]-'1')) {
        if (in > n)
            continue;
        if (mask&(num(1)<<in))
            continue;
        if (!bt(i+lp+1, (mask|(num(1)<<in)) ))
            continue;
        
        return 1;

    }
    
    ss--;
    return 0;
}

int main () {
    freopen("joke.in", "r", stdin);
    freopen("joke.out", "w", stdout);
    scanf(" %s", str);

    len = strlen(str);
    n = min(len, 9);
    
    n += (len-n)/2;

    for (int i = 0; i < n; i++)
        fin |= (1llu<<i);

    bt(0, num(0));
    int si = 1;
    for (int i = 0; i < len; i++) {
        if (si < ss && st[si] == i) {
            printf(" ");
            si++;
        }
        printf("%c", str[i]);
    }
    printf("\n");
}
