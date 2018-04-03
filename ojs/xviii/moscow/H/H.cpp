#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<int,int> pii;
#define pb push_back

const int N = 2e5+7;

char s[N];
int z[N]; // z[i] = |lcp(s, s[i...])|

void Z(int n) {
	int m = -1;
	for(int i = 1; i < n; i++) {
		z[i] = 0;
		if(m != -1 && m + z[m] >= i)
			z[i] = min(m + z[m] - i, z[i - m]);
		while(i + z[i] < n && s[i + z[i]] == s[z[i]]) z[i]++;
		if(m == -1 || i + z[i] > m + z[m])
			m = i;
	}
}

int n;

int dp[2][N]; // dp[k][n] = min len(a) where s[1..n] = ab and a is divided in k-1

int main () {
	scanf(" %s", s);
	n = strlen(s);
	Z(n);
	z[0] = n;
	
	for (int i = 0; i < n; i++) { dp[1][i] = 0; }
	//cout << endl;
	int mx = 1;
	for (int k = 2; k < 30; k++) {
		bool b = (k&1);
		
		set<int> s; // i
		set<pii> pres; // (len(a)+len(ab),len(ab))
		for (int i = 1; i <= n; i++) { // i = len(abc)
			while (pres.size() && pres.begin()->first <= i) {
				s.insert(pres.begin()->second);
				pres.erase(pres.begin());
			}
			while (s.size() && *s.begin() + min(*s.begin(),z[*s.begin()]) < i)
				s.erase(s.begin());
			if (s.size()) {
				dp[b][i] = *s.begin();
			} else {
				dp[b][i] = n+3;
			}
			//cout << "[" << k << "][" << i << "] = " << dp[b][i] << " ";
			//cout << "+(" << dp[!b][i]+i << " " << i << ")" << endl;
			pres.insert(pii(dp[!b][i]+i,i));
		}

		if (dp[b][n] != n+3)
			mx = max(mx,k);
	}
	printf("%d\n", mx);
}
