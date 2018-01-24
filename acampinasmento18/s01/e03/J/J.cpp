#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

map<string,int> nums;
map<char,vector<char> > self;
map<char,vector<char> > rem;
map<char,vector<char> > add;

int eval_num (char * c) {
	if (nums.find(c) == nums.end()) return INT_MAX;
	return nums[c];
}

int eval_expr (char * c, int mns = 0) {
	if (c[0] == 0) return INT_MAX;

	for (int k = 0; c[k]; k++) {
		if (c[k] == '-') {
			c[k] = 0;
			int a = eval_num(c);
			int b = eval_expr(c+k+1,1);
			int res = mns?-a+b:a + b;
			if (a == INT_MAX || b == INT_MAX) res = INT_MAX;
			c[k] = '-';
			return res;
		}
		if (c[k] == '+') {
			c[k] = 0;
			int a = eval_num(c);
			int b = eval_expr(c+k+1);
			int res = mns?-a+b:a + b;
			if (a == INT_MAX || b == INT_MAX) res = INT_MAX;
			c[k] = '+';
			return res;
		}
	}

	int a = eval_num(c);
	if (a == INT_MAX) return a;
	return mns?-a:a;
}

const int N = 107;
char saux[N];
set<string> st;

bool eval_state (char * c) {
	int s = 0;
	for (int i = 0; c[i]; i++) {
		if (c[i] != '?')
			saux[s++] = c[i];
	}
	saux[s++] = 0;
	c = saux;
	//printf("Try: %s\n", c);

	bool ok = 0;
	int eq = 0;
	for (int k = 0; c[k]; k++) { 
		if (c[k] != '=') continue;
		eq++;
		if (eq > 1) return 0;
		c[k] = 0;
		int a = eval_expr(c);
		int b = eval_expr(c+k+1);
		ok = (a==b);
		if (a == INT_MAX || b == INT_MAX) ok = 0;
		c[k] = '=';
		if (!ok) return 0;
	}

	if (ok) {
		if (st.find(saux) == st.end()) {
			st.insert(saux);
			return 1;
		} else {
			return 0;
		}
	}
	return 0;
}


char str[N];
char aux[N];

int main () {
	for (int i = 1; i < 90; i++) {
		int s = 0;
		if (i/10 == 8) { str[s++] = 'L'; str[s++] = 'X'; str[s++] = 'X'; str[s++] = 'X'; }
		else if (i/10 == 7) { str[s++] = 'L'; str[s++] = 'X'; str[s++] = 'X'; }
		else if (i/10 == 6) { str[s++] = 'L'; str[s++] = 'X'; }
		else if (i/10 == 5) { str[s++] = 'L'; }
		else if (i/10 == 4) { str[s++] = 'X'; str[s++] = 'L'; }
		else if (i/10 == 3) { str[s++] = 'X'; str[s++] = 'X'; str[s++] = 'X'; }
		else if (i/10 == 2) { str[s++] = 'X'; str[s++] = 'X'; }
		else if (i/10 == 1) { str[s++] = 'X';  }
		if (i%10 == 9) { str[s++] = 'I'; str[s++] = 'X'; }
		if (i%10 == 8) { str[s++] = 'V'; str[s++] = 'I'; str[s++] = 'I'; str[s++] = 'I'; }
		if (i%10 == 7) { str[s++] = 'V'; str[s++] = 'I'; str[s++] = 'I'; }
		if (i%10 == 6) { str[s++] = 'V'; str[s++] = 'I'; }
		if (i%10 == 5) { str[s++] = 'V'; }
		if (i%10 == 4) { str[s++] = 'I'; str[s++] = 'V'; }
		if (i%10 == 3) { str[s++] = 'I'; str[s++] = 'I'; str[s++] = 'I'; }
		if (i%10 == 2) { str[s++] = 'I'; str[s++] = 'I';  }
		if (i%10 == 1) { str[s++] = 'I'; }
		str[s++] = 0;
		nums[str] = i;
	}

	scanf(" %s", str);

	rem['L'].pb('I');
	rem['+'].pb('I');
	rem['+'].pb('-');
	rem['='].pb('-');
	rem['-'].pb('?');
	rem['I'].pb('?');
	add['I'].pb('L');
	add['I'].pb('+');
	add['-'].pb('=');
	add['-'].pb('+');
	//self['I'].pb('-');
	self['L'].pb('+');
	self['='].pb('+');
	self['V'].pb('X');
	//self['-'].pb('I');
	self['+'].pb('L');
	self['+'].pb('=');
	self['X'].pb('V');

	for (int i = 0; str[i]; i++) {
		char f = str[i];
		for (int j = 0; str[j]; j++) {
			char g = str[j];
			if (i == j) {
				for (char a : self[f]) {
					str[i] = a;
					if (eval_state(str)) printf("%s\n", saux);
				}
			} else {
				for (char a : rem[f]) {
					for (char b : add[g]) {
						str[i] = a;
						str[j] = b;
						if (eval_state(str)) printf("%s\n", saux);
					}
				}
			}
			str[i] = f;
			str[j] = g;
		}
	}

	for (int i = -1; i < 0 || str[i]; i++) {
		int s = 0;
		for (int j = 0; j <= i; j++) aux[s++] = str[j];
		aux[s++] = '_';
		for (int j = i+1; str[j]; j++) aux[s++] = str[j];
		aux[s++] = 0;

		for (int j = 0; aux[j]; j++) {
			char f = aux[j];
			for (char a : rem[f]) {
				for (char b : {'I','-'}) {
					aux[j] = a;
					aux[i+1] = b;
					if (eval_state(aux)) printf("%s\n", saux);
				}
			}
			aux[i+1] = '_';
			aux[j] = f;
		}
	}
}

