#include <bits/stdc++.h>

using namespace std;

const int N = 100007;

int n, t;
int df;
int ca, cb;
int edd, ee, edc, ja;
char stra[N], strb[N];

inline char getOutra (char a, char b) {
    for (char i = 'a'; i <= 'z'; i++) {
        if (i == a)
            continue;
        else if (i == b)
            continue;
        else
            return i;
    }
}

void fail () {
    printf("-1\n");
    exit(0);
}

int main () {
    scanf("%d %d", &n, &t);

    scanf(" %s %s", stra, strb);

    if (t > n) {
        fail();
    }
    
    df = 0;
    for (int i = 0; i < n; i++)
        df += (stra[i] != strb[i]);

    if (df <= t) {
        edd = df;
        ee = t-df;
    } else {
        edd = df%2;
        t -= edd;
        df -= edd;
        if (df/2 > t)
            fail();
        edc = df/2;
        ee = t-edc;
    }

    for (int i = 0; i < n; i++) {
        if (stra[i] == strb[i]) {
            if (ee) {
                printf("%c", getOutra(stra[i], strb[i]));
                ee--;
            } else {
                printf("%c", stra[i]);
            }
        } else {
            if (edc) {
                if (ja) {
                    printf("%c", stra[i]);
                    ja = 0;
                    edc--;
                } else {
                    printf("%c", strb[i]);
                    ja = 1;
                }
            } else if (edd) {
                printf("%c", getOutra(stra[i], strb[i]));
                edd--;
            }
        }
    }
}
