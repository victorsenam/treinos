#include <bits/stdc++.h>

using namespace std;

const int N = 20;

char str[N];
char res[N];
int freq[N];

int main () {
    while (scanf(" %s", str) != EOF ){
        for (int i = 0; i < 10; i++)
            freq[i] = 0;

        bool ok = 1;
        bool pre = 1;
        int top = '9';
        for (int i = 0; ok && str[i] != 0; i++) {
            if (pre) {
                if (freq[str[i]-'0'] < 2) {
                    res[i] = str[i];
                    freq[str[i]-'0']++;
                } else {
                    int j = str[i]-1;      
                    while (j >= '0' && freq[j-'0'] > 2) j--;
                    if (j < '0') {
                        pre = 0;
                        ok = 0;
                    } else {
                        res[i] = j;
                        freq[j-'0']++;
                        pre = 0;
                    }
                }
            } else {
                while (top >= '0' && freq[top-'0'] > 2) top--;
                if (top < '0') {
                    ok = 0;
                } else {
                    res[i] = top;
                    freq[top-'0']++;
                }
            }
        }

        if (!ok) {
            for (int i = 0; !i || str[i+1] != 0; i++)
                res[i] = '9'-(i/2);
        }
        printf("%s\n", res);
    }
}
