#include <bits/stdc++.h>
using namespace std;

class ConstructLCS { 
    public: 
    string construct(int ab, int bc, int ca) {
        int mn = min({ab,bc,ca});
        int c_ab = 0, c_bc = 0, c_ca = 0;

        if (ab != mn) {
            c_ab = 1;
        } else {
            c_bc = 1;
        }

        string res;
        for (int i = 0; i < mn; i++)
            res.push_back('0');
        for (int i = mn; i < ab; i++)
            res.push_back('0'+c_ab);
        for (int i = mn; i < ca; i++)
            res.push_back('0'+c_ca);
        res.push_back(' ');
        for (int i = 0; i < mn; i++)
            res.push_back('0');
        for (int i = mn; i < ab; i++)
            res.push_back('0'+c_ab);
        for (int i = mn; i < bc; i++)
            res.push_back('0'+c_bc);
        res.push_back(' ');
        for (int i = 0; i < mn; i++)
            res.push_back('0');
        for (int i = mn; i < bc; i++)
            res.push_back('0'+c_bc);
        for (int i = mn; i < ca; i++)
            res.push_back('0'+c_ca);
        return res;
    }
    
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 3; int Arg1 = 4; int Arg2 = 2; string Arg3 = "101 1010101 1111"; verify_case(0, Arg3, construct(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 7; int Arg1 = 4; int Arg2 = 4; string Arg3 = "10101010 1010101 1011"; verify_case(1, Arg3, construct(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 8; int Arg1 = 7; int Arg2 = 8; string Arg3 = "110101001011 010101101 10101010"; verify_case(2, Arg3, construct(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 8; int Arg1 = 6; int Arg2 = 7; string Arg3 = "110101010 10101010 1111010"; verify_case(3, Arg3, construct(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arg0 = 15; int Arg1 = 17; int Arg2 = 19; string Arg3 = "000100101101111011000 11110111010011101010 100100001010101001010101000011111"; verify_case(4, Arg3, construct(Arg0, Arg1, Arg2)); }
	void test_case_5() { int Arg0 = 50; int Arg1 = 50; int Arg2 = 50; string Arg3 = "11111111111111111111111111111111111111111111111111 11111111111111111111111111111111111111111111111111 11111111111111111111111111111111111111111111111111"; verify_case(5, Arg3, construct(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE 
int main() {
    ConstructLCS ___test; 
        ___test.run_test(-1); 
    } 
// END CUT HERE 
    
