#include <bits/stdc++.h>
using namespace std;
class SubstitutionCipher { 
	public:
	string decode(string a, string b, string y) {
        char map[300];
        bool set[300];

        memset(set, 0, sizeof set);
        memset(map, 0, sizeof map);

        int cnt = 0;

        for (int i = 0; i < a.size(); i++) {
            if (set[a[i]] == 1 && map[b[i]] != a[i])
                return (string) "";
            else
                cnt++;

            map[b[i]] = a[i];
            set[a[i]] = 1;
        }
        
        int la = 0;
        int lb = 0;
        for (int i = 'A'; i <= 'Z'; i++) {
            if (set[i] == 0) {
                if (lb)
                    lb = 1;
                else
                    lb = i;
            }
            if (map[i] == 0) {
                if (la)
                    la = 1;
                else
                    la = i;
            }
        }
        if (la > 1 && lb > 1) {
            map[la] = lb;
            set[lb] = 1;
        }

        for (int i = 0; i < y.size(); i++) {
            if (map[y[i]] == 0) {
                return (string) "";
            }
            y[i] = map[y[i]];
        }
        return y;
	} 

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "CAT"; string Arg1 = "DOG"; string Arg2 = "GOD"; string Arg3 = "TAC"; verify_case(0, Arg3, decode(Arg0, Arg1, Arg2)); }
	void test_case_1() { string Arg0 = "BANANA"; string Arg1 = "METETE"; string Arg2 = "TEMP"; string Arg3 = ""; verify_case(1, Arg3, decode(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arg0 = "THEQUICKBROWNFOXJUMPSOVERTHELAZYHOG"; string Arg1 = "UIFRVJDLCSPXOGPYKVNQTPWFSUIFMBAZIPH"; string Arg2 = "DIDYOUNOTICESKIPPEDLETTER"; string Arg3 = "CHCXNTMNSHBDRJHOODCKDSSDQ"; verify_case(2, Arg3, decode(Arg0, Arg1, Arg2)); }

// END CUT HERE
 
}; 

// BEGIN CUT HERE 
int main() {
SubstitutionCipher ___test; 
___test.run_test(-1); 
} 
// END CUT HERE 
