#include <bits/stdc++.h>

using namespace std;

#define N 200

int n, m, r, p[2], c, a;
bool ok, v[N*N];
char s[N*N];
queue<int> q;

bool liv (int a) {
    int k = 0;
    if (a/m == (a+1)/m && s[a+1] == '1') k++;
    if (a/m == (a-1)/m && s[a-1] == '1') k++;
    if (a+m < n*m && s[a+m] == '1') k++;
    if (a-m >= 0 && s[a-m] == '1') k++;

    printf("liv(%d, %d) = %d\n", a/m, a%m, k==1);
    return (k==1);
}

bool ext (int a) {
    printf("ext(%d, %d)\n");
    if (a/m == (a+1)/m && liv(a+1)) return 1;
    if (a/m == (a-1)/m && liv(a-1)) return 1;
    if (a+m < n*m && liv(a+m)) return 1;
    if (a-m >= 0 && liv(a-m)) return 1;
    printf("\t false\n");
    return 0;
}

int main () {
    while (scanf("%d %d", &n, &m) != EOF && n && m) {
        for (int i = 0; i < n*m; i++) {
            scanf(" %c", &s[i]);
            v[i] = 0;
        }

        r = 0;
        
        for (int i = 0; i < n*m; i++) {
            if (s[i] != '1' || v[i]) continue;

            q.push(i);
            p[0] = p[1] = -1;
            ok = 1;

            while (!q.empty()) {
                a = q.front();
                q.pop();
                v[a] = 1;
                c = 0;

                if (a/m == (a+1)/m && s[a+1]=='1') {
                    c++;
                    if (!v[a+1]) q.push(a+1);
                }
                if (a/m == (a-1)/m && s[a-1]=='1') {
                    c++;
                    if (!v[a-1]) q.push(a-1);
                }
                if (a+m < n*m && s[a+m]=='1') {
                    c++;
                    if (!v[a+m]) q.push(a+m);
                }
                if (a-m >= 0 && s[a-m] == '1') {
                    c++;
                    if (!v[a-m]) q.push(a-m);
                }

                if (c == 1) {
                    if (p[0] == -1)
                        p[0] = a;
                    else if (p[1] == -1)
                        p[1] = a;
                    else
                        ok = 0;
                }
            }

            if (!ok || p[0] == -1) continue;
            if (!ext(p[0]) && (p[1] == -1 || !ext(p[1]))) r++;
        }

        printf("%d\n", r);
    }
}
