#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int M = 30;

int ts;
int n, m;
char str[M];
vector<int> q;
int v[M];

void printa (int x) {
	for (int i = 0; i < m; i++)
		printf("%d", !!(x&(1<<(m-i-1))));
}

int getcor (int a, int b, int m) {
	int rs = 0;
	for (int i = 0; i < m; i++)
		rs += ((a&(1<<i)) == (b&(1<<i)));
	return rs;
}

int main () {
	scanf("%d", &ts);

	while (ts--) {
		int qt = 0;
		int sl = -1;
		map<vector<int>, int> mp;
		map<vector<int>, int> buil;
		scanf("%d %d", &n, &m);

		q.resize(n);
		for (int i = 0; i < n; i++) {
			scanf(" %s %d", str, &q[i]);
			v[i] = 0;
			for (int j = 0; j < m; j++) {
				v[i] *= 2;
				v[i] += (str[j] == '1');
			}
		}
	
		for (int ms = 0; ms < (1<<(m/2)); ms++) {
			//printf("%s:", bitset<3>(ms).to_string().c_str());
			vector<int> c(n,0);
			for (int i = 0; i < n; i++) {
				c[i] = getcor(ms, v[i], m/2);
				//printf(" %d", c[i]);
			}
			//printf("\n");
			mp[c]++;
			buil[c] = ms;
		}

		//printf("===\n");
		for (int ms = 0; ms < (1<<(m-m/2)); ms++) {
			//printf("%s:", bitset<3>(ms).to_string().c_str());
			vector<int> c = q;
			for (int i = 0; i < n; i++) {
				c[i] = q[i] - getcor(ms, (v[i]>>(m/2)), m-(m/2));
				//printf(" %d", c[i]);
			}
			//printf("\n");
			int val = mp[c];
			if (val) {
				qt += val;
				sl = (buil[c]);
				sl += (ms << (m/2));
			}
		}

		if (qt == 1)
			printa(sl);
		else
			printf("%d solutions", qt);
		printf("\n");
	}
}
