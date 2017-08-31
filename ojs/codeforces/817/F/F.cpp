#include <bits/stdc++.h>
#define cout if (0) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef ll tA;
typedef null_type tB; // or null_type if you want a set
typedef tree<tA, tB, less<tA>, rb_tree_tag, tree_order_statistics_node_update> ord_set;
// map: tA -> tB com comparador less<tA>
// pode usar como um map normalmente
// s.find_by_order(k) :: retorna iterador para o k-esimo elemento (0-index) (ou s.end())
// s.order_of_key(x)  :: retorna a qtd de elementos estritamente menores que x

int n;
ord_set s;

void rev (ll x) {
	if (s.find(x) == s.end()) {
		s.insert(x);
		cout << "+" << x << endl;
	} else { 
		s.erase(x);
		cout << "-" << x << endl;
	}
}

int isin (ll x) {
	int o = (int) s.order_of_key(x+1);
	//printf("%lld é maior que %d\n", x, o);
	return !(o%2);
}

int main () {
	scanf("%d", &n);
	s.insert(1);
	cout << "+" << 1 << endl;
	for (int i = 0; i < n; i++) {
		int t; ll l, r;
		scanf("%d %lld %lld", &t, &l, &r);
		r++;
		
		if (t == 3) {
			rev(l);
			rev(r);
		} else {
			int ini = isin(r);
			ord_set::iterator it = s.lower_bound(l);
			while (it != s.end() && *it < r) {
				ord_set::iterator nx = next(it);
				cout << "-" << *it << endl;
				s.erase(it);
				it = nx;
			}

			int is = isin(l);
			if ((t == 1 && !is) || (t == 2 && is)) { 
				s.insert(l);
				cout << "+" << l << endl;
			}

			//printf("%lld foi de %d pra %d\n", r, ini, isin(r));

			if (ini != isin(r))
				rev(r);
		}
		printf("%lld\n", (*s.begin()));
	}
}
