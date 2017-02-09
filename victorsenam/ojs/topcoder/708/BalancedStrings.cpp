#line 2 "BalancedStrings.cpp"
#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

class BalancedStrings {
    public:
    vector <string> findAny(int N) {
        if (N == 1)
            return vector<string>({"w"});

        int sim = 0;
        int dif = 0;
        int cyc = 0;
        vector<string> res({"w", "y"});

        int lt = 0;
        while (res.size() < N) {
            string att("");
            att.push_back('a' + lt);

            sim += cyc;
            lt++;
            if ('a'+lt == 'w') {
                lt = 0;
                cyc++;
            }

            while (dif < sim) {
                if (res[0].size() < 100) {
                    res[0].push_back('w' + !(dif%2));
                } else {
                    res[1].push_back('y' + (dif%2));
                }
                dif++;
            }

            res.push_back(att);
        }

        return res;
    }
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <string> &Expected, const vector <string> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { int Arg0 = 3; string Arr1[] = {"eertree", "topcoder", "arena" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(0, Arg1, findAny(Arg0)); }
	void test_case_1() { int Arg0 = 4; string Arr1[] = {"hello", "little", "polar", "bear" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(1, Arg1, findAny(Arg0)); }
	void test_case_2() { int Arg0 = 5; string Arr1[] = {"abbbbbbbbbbbbczaaaaaao", "c", "zz", "c", "xxxyyyzvvv" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(2, Arg1, findAny(Arg0)); }
	void test_case_3() { int Arg0 = 1; string Arr1[] = {"kkkkkkkkkkkkkkkkkkk" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(3, Arg1, findAny(Arg0)); }
	void test_case_4() { int Arg0 = 99; string Arr1[] = {"asdflkjhsdfsfffkdhjfdlshlfds", "pudelek", "xo", "xo", "mnbvmnmbbr", "plox", "qqwwrrttyyy", "you", "are", "awesome" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(4, Arg1, findAny(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main () {
    BalancedStrings ___test; 
    ___test.run_test(-1);
}
// END CUT HERE
