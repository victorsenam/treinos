#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

string s;
int n;
int cn;

void go () {
	if (cn < 0) {
		return;
	} else if (s.size() == n) {
		if (cn == 0)
			printf("%s\n", s.c_str());
	} else {
		cn++;
		s.push_back('(');
		go();

		cn--;
		s.pop_back();

		cn--;
		s.push_back(')');
		go();

		cn++;
		s.pop_back();
	}
}

int main () {
	scanf("%d", &n);
	n += n;
	cn = 0;
	go();
}
