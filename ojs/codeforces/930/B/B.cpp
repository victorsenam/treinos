#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 5003;

char str[N];
vector<int> f[29];
int on[500], tw[500];

int main () {
	scanf(" %s", str);
	int n = 0;
	for (int i = 0; str[i]; n++, i++)
		f[str[i]-'a'].pb(i);

	ll res = 0;
	for (char c = 'a'; c <= 'z'; c++) {
		for (char a = 'a'; a <= 'z'; a++) { on[a] = -1; tw[a] = -1; }
		int loc = 0;
		for (int i = 1; i < n; i++) {
			int r = 0;
			for (int p : f[c-'a']) {
				if (on[str[(i+p)%n]] != i) { on[str[(i+p)%n]] = i; r++; }
				else if (tw[str[(i+p)%n]] != i) { tw[str[(i+p)%n]] = i; r--; }
			}
			loc = max(loc, r);
		}
		res += loc;
	}
	printf("%.20f\n", double(res)/n);

}
