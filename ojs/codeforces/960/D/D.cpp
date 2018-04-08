#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

int q;
map<ll,ll> val, nod;

ll lvl (ll u) { ll c = 0; for (c = 0; u; c++, u /= 2); return c; }

int main () {
	scanf("%d", &q);
	
	while (q--) {
		int t;
		scanf("%d", &t);
		if (t == 3) {
			ll u;
			scanf("%lld", &u);

			do {
				printf("%lld", u);
				if (u == 1) break;
				ll lv = lvl(u);
				ll qt = (1ll<<(lv-1));
				// shifta o quanto esse cara mudou pros pais
				u = ((((u-qt+nod[lv])%qt) + qt)%qt) + qt;
				//cout << "[" << u << "]";
				printf(" ");
				u /= 2;
				// shifta o quanto esse cara mudou pros filhos
				lv--; qt /= 2;
				u = ((((u-qt+val[lv])%qt) + qt)%qt) + qt;
			} while (u);
			printf("\n");
		} else if (t == 1) {
			ll u, x;
			scanf("%lld %lld", &u, &x);
			ll lv = lvl(u);
			ll qt = (1ll<<(lv-1));
			val[lv] -= x;
			val[lv] = ((val[lv]%qt) + qt)%qt;
			nod[lv] += x;
			nod[lv] = ((nod[lv]%qt) + qt)%qt;
		} else {
			ll u, x;
			scanf("%lld %lld", &u, &x);
			ll lv = lvl(u);
			ll qt = (1ll<<(lv-1));
			nod[lv] += x;
			nod[lv] = ((nod[lv]%qt) + qt)%qt;
		}
	}
}
