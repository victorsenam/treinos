#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

char s[1123456];

int main () {
	scanf("%s", s);
	vector<char> st;
	string pref;
	string suf;
	string a = "()[]{}";
	for(int i = 0; s[i]; i++) {
		int j;
		for(j = 0; a[j] != s[i]; j++);
		if(j & 1) {
			if(st.empty()) {
				pref.pb(a[j - 1]);
			} else if(st.back() == a[j - 1]) st.pop_back();
			else {
				puts("NIE");
				return 0;
			}
		} else {
			st.pb(s[i]);
		}
	}
	while(!st.empty()) {
		int j;
		for(j = 0; a[j] != st.back(); j++);
		suf.pb(a[j + 1]);
		st.pop_back();
	}
	reverse(pref.begin(), pref.end());
	printf("%s%s%s\n", pref.c_str(), s, suf.c_str());
}
