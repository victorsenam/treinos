#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define GNU __gnu_pbds

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
namespace GNU { typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set; } 
// null_type pode mudar pra virar map
// multiset e multimap não tem suporte aqui, tem que sair usando pair pelo jeito
// aquele less ali é o comparador, louco né?
using GNU::ordered_set;

#ifdef ONLINE_JUDGE
#define lld I64d
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

ordered_set s;
int q;
int a;

int main () {
    while (scanf("%d %d", &q, &a) != EOF) {
        if (q == 1) {
            s.insert(a);
        } else if (q == 2){ 
            if (end(s) == s.find_by_order(a))
                printf("no\n");
            else
                printf("%d\n", (int) *s.find_by_order(a)); // se você esquecer do cast ou do *, o gcc vai falar que sua família não presta
        } else {
            printf("%d\n", (int) s.order_of_key(a));
        }
    }
    
}
