#include <bits/stdc++.h>

using namespace std;

const int N = 1007;

int t, cnt, maxi, d;
char str[N];
int freq[26];

int main () {
    scanf("%d", &t);

    while (t--) {
        memset(freq, 0, sizeof(freq));

        scanf(" %[A-Z ]", str);

        for (int i = 0; str[i] != '\0'; i++) {
            if (str[i] == ' ') continue;
            freq[str[i]-'A']++;
        }
        
        cnt = 0;
        maxi = 0;
        for (int i = 0; i < 26; i++) {
            if (freq[i] > freq[maxi]) {
                maxi = i;
                cnt = 1;
            } else if (freq[i] == freq[maxi])
                cnt++;
        }

        if (cnt > 1)
            printf("NOT POSSIBLE\n");
        else {
            d = ((maxi-4)%26+26)%26;
            printf("%d ", d);
            for (int i = 0; str[i] != '\0'; i++) {
                if (str[i] == ' ')
                    printf(" ");
                else
                    printf("%c", ((str[i]-'A')-d+26)%26+'A');
            }
            printf("\n");
        }
    }
}
