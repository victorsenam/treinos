#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 30;
int cnt = 0;
char str[N];
string tb[300];
bool fl = 0;
int msk[400];

int avail (int i, int j, int v, int t) {
	if (i > j) throw 0;
	if (t == 0) { // F
		if (str[i] == '!') return (1<<8) - 1 - avail(i+1,j,v,0);
		if (str[i] == '(') {
			if (str[j] != ')') throw 0;
			return avail(i+1,j-1,v,2);
		}
		if (i == j && str[i] >= 'x' && str[i] <= 'z') return msk[str[i]];
	} else if (t == 1) { // T
		for (int k = j; k >= i; k--) if (str[k] == '&')
			return avail(i,k-1,v,1) & avail(k+1,j,v,0);
		return avail(i,j,v,0);
	} else { // E
		for (int k = j; k >= i; k--) if (str[k] == '|') {
			return avail(i,k-1,v,2) | avail(k+1,j,v,1);
		}
		return avail(i,j,v,1);
	}
	throw 0;
}

void go (int i, int n) {
	if (i == n) {
		int s = 0;
		fl = 0;
		try {
			s = avail(0,n-1,0,2);
			if (tb[s].size() == 0) {
				cnt++;
				cout << cnt << " " << s << " -> " << str << endl;
				tb[s] = str;
			}
		} catch (int e) {
		}
	} else {
		for (char c : {'!','&','(',')','x','y','z','|'}) {
			str[i] = c;
			go(i+1,n);
		}
	}
}

int main () {
	msk['x'] = (((1<<4)-1)<<4);
	msk['y'] = (((1<<2)-1)<<2) + (((1<<2)-1)<<6);
	msk['z'] = 2 + 8 + 32 + 128;
	cout << msk['x'] << " " << msk['y'] << " " << msk['z'] << endl;
	for (int i = 1; i < 12; i++) {
		str[i] = 0;
		go(0,i);
		cout << "len " << i << endl;
	}
	cout << cnt << endl;
}
