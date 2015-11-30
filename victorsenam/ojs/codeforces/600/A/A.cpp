#include <bits/stdc++.h>

using namespace std;

const int N = 100007;

char str[N];
int ka, kb;
bool ua, ub;
char a[N], b[N];

int main () {
    scanf(" %s", str);

    ka = kb = 0;
    ua = ub = 0;
    int ls = 0;
    bool haschar = 0;
    bool hasld0 = 0;
    for (int i = 0; !i || str[i-1] != '\0'; i++) {
        if (str[i] == '\0' || str[i] == ',' || str[i] == ';') {
            if (haschar || (hasld0 && i != ls+1) || ls == i) {
                if (ub)
                    b[kb++] = ',';
                for (int j = ls; j < i; j++)
                    b[kb++] = str[j];
                ub = 1;
            } else {
                if (ua)
                    a[ka++] = ',';
                for (int j = ls; j < i; j++)
                    a[ka++] = str[j];
                ua = 1;
            }

            ls = i+1;
            haschar = hasld0 = 0;
        } else if (str[i] < '0' || str[i] > '9') {
            haschar = 1;
        } else if (i == ls && str[i] == '0') {
            hasld0 = 1;
        }
    }
    a[ka++] = b[kb++] = '\0';
    if (ua)
        printf("\"%s\"\n", a);
    else
        printf("-\n");

    if (ub)
        printf("\"%s\"\n", b);
    else
        printf("-\n");
}
