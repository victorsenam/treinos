#include <bits/stdc++.h>

/**/


using namespace std;

const int N = 1003;

char sa[N], sm[N];
int n;

void getMax(int a) {
    bool chn = 0;
    for (int i = 0; i < n && !chn; i++) {
        if (sa[(i+a)%n] < sm[i])
            chn = 1;
        if (sa[(i+a)%n] > sm[i])
            return;
    }
    
    if (!chn)
        return;

    for (int i = 0; i < n; i++) {
        sm[i] = sa[(i+a)%n];
    }
}

int main () {
    scanf("%d", &n);

    scanf(" %s", sa);
    for (int i = 0; i < n; i++) {
        sa[i] -= '0';
        sm[i] = sa[i];
    }

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < n; j++)
            sa[j] = (sa[j]+1)%10;       

        for (int j = 0; j < n; j++)
            getMax(j);
    }

    for (int i = 0; i < n; i++) {
        printf("%d", sm[i]);
    }
    printf("\n");
}
