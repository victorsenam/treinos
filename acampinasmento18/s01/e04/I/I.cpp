#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 300;
char t[N];
char s[N];

bool isNm (char a) {
	return (a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z');
}

int main () {
#ifdef ONLINE_JUDGE
	freopen("isharp.in", "r", stdin);
	freopen("isharp.out", "w", stdout);
#endif

	scanf("%s", t);
	int n = strlen(t);
	
	while (scanf("%s", s) != EOF) {
		int m = strlen(s);
		int c = n;
		s[--m] = 0;

		while (!isNm(s[m-1])) {
			if (s[m-1] == '[') s[m-1] = ']';
			else if (s[m-1] == ']') s[m-1] = '[';
			t[c++] = s[--m];
		}
		s[m] = 0;
		t[c++] = 0;
		printf("%s %s;\n", t, s);
		c = n;
	}
}
