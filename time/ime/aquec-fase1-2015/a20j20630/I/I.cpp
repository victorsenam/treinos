#include <bits/stdc++.h>

using namespace std;

const int N = 26;

int t;
char c, v;
int cs[N];
set<int> s;
set<int>::iterator it;

int main() {
    scanf("%d", &t);

    while (t--) {
        for (int i = 0; i < 52; i++)
            s.insert(i);
        for (int i = 0; i < N; i++) {
            scanf(" %c%c", &v, &c);
            if (v >= '2' && v <= '9')
                cs[i] = (v-'2')*4;
            else if (v == 'T')
                cs[i] = 8*4;
            else if (v == 'J')
                cs[i] = 9*4;
            else if (v == 'Q')
                cs[i] = 10*4;
            else if (v == 'K')
                cs[i] = 11*4;
            else
                cs[i] = 12*4;

            if (c == 'D');
            else if (c == 'C')
                cs[i]+=1;
            else if (c == 'H')
                cs[i]+=2;
            else
                cs[i]+=3;

            s.erase(cs[i]);
        }

        sort(cs, cs+N);
        
        int res = 0;
        for (int i = 0; i < N; i++) {
            it = s.lower_bound(cs[i]);
            if (it == s.begin()) {
                it = s.lower_bound(52);
                s.erase(--it);
            } else {
                s.erase(--it);
                res++;                
            }
        }
        printf("%d\n", res);
    }
}
