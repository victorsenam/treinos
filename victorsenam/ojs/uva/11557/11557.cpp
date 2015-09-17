#include <bits/stdc++.h>

using namespace std;

const int N = 107;
const int S = 257;
const int M = 10007;
const string ender = "***END***";

int lins[N];
string code[N][M];
char name[N][S];
char temp[S];
int n;
set<int> res;
set<int>::iterator it;
int maxi;

int main () {
    while (scanf("%d", &n) != EOF) {
        for (int i = 0; i <= n; i++) {
            lins[i] = 0;
            if (i < n)
                scanf(" %[ -~]", name[i]);

            while (scanf(" %[ -~]", temp) && strcmp(temp, ender.c_str())) {
                int k = 0;
                for (int j = 0; temp[j] != '\0'; j++)
                    if (temp[j] != temp[j+1] || temp[j] != ' ')
                        temp[k++] = temp[j];
                temp[k++] = '\0';
                if (k == 1)
                    continue;
                code[i][lins[i]++] = temp;
            }
        }

        maxi = 0;
        res.clear();

        for (int i = 0; i < n; i++) {
            int att = 0;
            for (int j = 0; j < min(lins[i], lins[n]); j++) {
                if (strcmp(code[i][j].c_str(), code[n][j].c_str()) == 0)
                    att++;

                if (!att)
                    continue;

                if (att > maxi) {
                    maxi = att;
                    res.clear();
                }
                if (maxi == att)
                    res.insert(i);
            }
        }

        printf("%d", maxi);
        for (it = res.begin(); it != res.end(); it++)
            printf(" %s", name[*it]);
        printf("\n");
    }
}
