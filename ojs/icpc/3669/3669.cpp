#include <bits/stdc++.h>

using namespace std;

#define K 1000
#define N 10002

set<int> s;
set<int>::iterator it;
int k, t, v[N][30], lo, mid, hi;
unsigned long long int c;
int cs[K], i;
char e[N];

int main () {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &k);
        for (i = 0; i < k; i++) scanf("%d", &cs[i]);
        scanf(" %s", e);
        
        for (int j = 0; j <= 'z'-'a'; j++) v[0][j] = 0;

        for (i = 0; e[i] != '\0'; i++) {
            for (int j = 0; j <= 'z'-'a'; j++) v[i+1][j] = v[i][j];
            v[i+1][e[i]-'a']++;
        }

        s.clear();
        s.insert(0);
        s.insert(i);

        /*
        for (int j = 0; j <= 'd'-'a'; j++) {
            printf("%c 0 ", j+'a');
            for (i = 0; e[i] != '\0'; i++) {
                printf("%d ", v[i+1][j]);
            }
            printf("\n");
        }
        */
   
        c = 0;

        for (i = 0; i < k; i++) {
            it = s.insert(cs[i]).first;

            it--;
            lo = *it;
            it++;
            mid = *it;
            it++;
            hi = *it;

            for (int j = 0; j <= 'z'-'a'; j++) {
                int a = 0;
                if ((v[mid][j]-v[lo][j])) a++;
                if ((v[hi][j]-v[mid][j])) a++;
                if (a==1) c++;
            }
        }

        printf("%llu\n", c);
    }
}
