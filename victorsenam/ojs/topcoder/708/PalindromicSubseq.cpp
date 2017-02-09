#line 2 "PalindromicSubseq.cpp"
#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

const int N = 3e3+7;
const ll MOD = 1e9+7;

string t;
int memo[N][N];

int pd (int i, int j) {
    if (i < 0 || j >= t.size())
        return 0;

    int & me = memo[i][j];
    if (me != -1) return me;

    if (t[i] != t[j])
        me = (MOD - pd(i-1,j+1))%MOD;
    else
        me = 1;

    me = (me + pd(i-1,j))%MOD;
    me = (me + pd(i,j+1))%MOD;
    return me;
}

class PalindromicSubseq {
    public:
    int solve(string s) {
        memset(memo, -1, sizeof memo);
        t = s;
        int res = 0;
        for (int i = 0; i < s.size(); i++) {
            int loc = pd(i-1,i+1)+1;
            loc %= MOD;
            loc *= (i+1);
            loc %= MOD;
            res ^= loc;
            printf("%d ", pd(i-1,i+1)+1);
        }
        printf("\n");
        return res;
    }
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "aaba"; int Arg1 = 30; verify_case(0, Arg1, solve(Arg0)); }
	void test_case_1() { string Arg0 = "abcd"; int Arg1 = 4; verify_case(1, Arg1, solve(Arg0)); }
	void test_case_2() { string Arg0 = "tcoct"; int Arg1 = 60; verify_case(2, Arg1, solve(Arg0)); }
	void test_case_3() { string Arg0 = "zyzyzzzzxzyz"; int Arg1 = 717; verify_case(3, Arg1, solve(Arg0)); }
	void test_case_4() { string Arg0 = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"; int Arg1 = 1025495382; verify_case(4, Arg1, solve(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main () {
    PalindromicSubseq ___test; 
    ___test.run_test(-1);
}
// END CUT HERE
