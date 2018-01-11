class GameOfInterval { 
    public: 
    string construct(int n) {
    }
    
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 4; string Arg1 = "0102"; verify_case(0, Arg1, construct(Arg0)); }
	void test_case_1() { int Arg0 = 6; string Arg1 = "00010102020303040405000301040205"; verify_case(1, Arg1, construct(Arg0)); }
	void test_case_2() { int Arg0 = 5; string Arg1 = "00010001"; verify_case(2, Arg1, construct(Arg0)); }
	void test_case_3() { int Arg0 = 80; string Arg1 = ""; verify_case(3, Arg1, construct(Arg0)); }
	void test_case_4() { int Arg0 = 81; string Arg1 = "00010203"; verify_case(4, Arg1, construct(Arg0)); }
	void test_case_5() { int Arg0 = 1; string Arg1 = ""; verify_case(5, Arg1, construct(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE 
int main() {
    GameOfInterval ___test; 
        ___test.run_test(-1); 
    } 
// END CUT HERE 
    
