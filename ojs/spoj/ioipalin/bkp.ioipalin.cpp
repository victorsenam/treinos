/* Como descobrir que você não pode usar o algoritmo de LIS do Knuth pra resolver LCS */

#include <bits/stdc++.h>

using namespace std;

#define MAX 5001

int n;
char s[MAX];
vector<int> v, av;
multimap<char, int> m;

pair<multimap<char, int>::iterator, multimap<char, int>::iterator> rg;
multimap<char, int>::iterator it;
vector<int>::iterator jt;

int main () {
    scanf("%d", &n);
    scanf(" %s", s);
    
    int j = n;
    for (int i = 0; i < n; i++) {
        m.insert(make_pair(s[i], --j));
    }
    
    for (int i = 0; i < n; i++) {
//        printf("%c -> ", s[i]);
        rg = m.equal_range(s[i]);

        /* O erro acontece aqui quando você coloca uma string longa com várias repetições do mesmo caractere */
        for (it = rg.first; it != rg.second; it++) {
//            printf("%d ", it->second);
            jt = lower_bound(v.begin(), v.end(), it->second);

            if (jt == v.end()) v.push_back(it->second);
            else if (*jt > it->second) *jt = it->second;
        }

//        printf("-> ");
//        for (jt = v.begin(); jt < v.end(); jt++) {
//            printf("%d(%c) ", *jt, s[n-1-*jt]);
//        }
//        printf("\n");
    }

    printf("%d\n", n-v.size());
}
