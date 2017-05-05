#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define debug(...) {}
#endif

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back


const int N =400;
char str[N];
char c;
char sussu[] = "Sussu";

int main () {
    scanf("%[a-zA-Z ]", str);
    scanf("%c", &c);

    if (c == '?') {
        printf("7\n");
    } else {
        int n = strlen(str);
        for (int i = 0; i + 4 < n; i++) {
            bool ok = 1;
            for (int j = 0; j < 4; j++)
                if (str[i+j] != sussu[j])
                    ok = 0;
            if (str[i+5] >= 'a' && str[i+5] <= 'z')
                ok = 0;
            if (str[i+5] >= 'A' && str[i+5] <= 'Z')
                ok = 0;
            if (ok) {
                printf("AI SUSSU!\n");
                return 0;
            }
        }
        printf("O cara é bom!\n");
    }
}
