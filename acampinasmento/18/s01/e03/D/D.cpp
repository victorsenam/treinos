#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e5+7;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef pii tA;
typedef null_type tB;
typedef tree<tA,tB,less<tA>,rb_tree_tag,tree_order_statistics_node_update> ord_set;

int n;
char str[40], name[40];
int rel[N];
string bname[N];
map<string,int> mp;
ord_set s;

int main () {
	scanf("%d", &n);

	int curid = 0;
	for (int i = 0; i < n; i++) {
		scanf("%s", str);

		if (string(str) == "ISSUE") {
			scanf("%s", name);
			if (mp.find(name) != mp.end()) {
				int id = mp[name];
				printf("EXISTS %d %d\n", id, rel[id]);
			} else {
				rel[curid] = 0;
				bname[curid] = name;
				s.insert(pii(-rel[curid],curid));
				mp[name] = curid++;
				printf("CREATED %d 0\n", curid-1);
			}
		} else if (string(str) == "DELETE") {
			scanf("%s", name);
			if (mp.find(name) != mp.end()) {
				int id = mp[name];
				printf("OK %d %d\n", id, rel[id]);
				s.erase(pii(-rel[id],id));
				mp.erase(name);
			} else {
				printf("BAD REQUEST\n");
			}
		} else if (string(str) == "RELIABILITY") {
			int x;
			scanf("%s %d", name, &x);
			if (mp.find(name) != mp.end()) {
				int id = mp[name];
				s.erase(pii(-rel[id],id));
				rel[id] += x;
				s.insert(pii(-rel[id],id));
				printf("OK %d %d\n", id, rel[id]);
			} else {
				printf("BAD REQUEST\n");
			}
		} else {
			int n;
			scanf("%d", &n);
			if (s.empty()) {
				printf("EMPTY\n");
			} else {
				auto it = s.find_by_order(n);
				int id = prev(s.end())->second;
				if (it != s.end())
					id = it->second;
				printf("OK %s %d %d\n", bname[id].c_str(), id, rel[id]);
			}
		}
	}

}
