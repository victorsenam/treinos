#include <bits/stdc++.h>

using namespace std;
typedef int num;
#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#else
#define debug(...) //
#endif


#define N 101

char str[N];
int n;

int main () {
    scanf(" %s", str);

    for (n = 0; str[n] != '\0'; n++) {
        if (str[n] == '8' || str[n] == '0') {
            printf("YES\n");
            printf("%c\n", str[n]);
            return 0;
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        for (int j = i - 1; j >= 0; j--) {
            if (((str[j]-'0')*10 + (str[i]-'0'))%8 == 0) {
                printf("YES\n");
                printf("%c%c\n", str[j], str[i]);
                return 0;
            }
            for (int k = j - 1; k >= 0; k--) {
                if (((str[k]-'0')*100 + (str[j]-'0')*10 + (str[i]-'0'))%8 == 0) {
                    printf("YES\n");
                    printf("%c%c%c\n", str[k], str[j], str[i]);
                    return 0;
                }
            }
        }
    }

    printf("NO\n");
}
