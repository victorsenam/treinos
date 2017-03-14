#include <bits/stdc++.h>

using namespace std;
typedef int num;
#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#else
#define debug(...) //
#endif

#define N 27

char temp[N];
int n;
set<string> s;
char aux[N];

int main () {
    scanf(" %s", temp);

    for (int i = 0; i == 0 || temp[i-1] != '\0'; i++) {
        for (char c = 'a'; c <= 'z'; c++) {
           int j = 0;
           for (j = 0; j == 0 || temp[j-1] != '\0'; j++) {
               if (j < i) aux[j] = temp[j];
               else if (j == i) aux[j] = c;
               else aux[j] = temp[j-1];
           }
           aux[j] = '\0';
           s.insert(aux);
        }
    }
    printf("%d\n", (int) s.size());
}
