#include<string>
#include<cstdio>
#include<vector>
#include<iostream>

using namespace std;

class EightRooks {
    public:
    string static isCorrect(vector <string> board) {
        bool ok, rr, rc[8];
        int count;

        ok = 1;
        count = 0;

        for (int i = 0; i < 8; i++) rc[i] = 0;

        for (int i = 0; i < 8 && ok; i++) {
            rr = 0;
            for (int j = 0; j < 8 && ok; j++) {
                if (board[i][j] == 'R') {
                    if (rr) ok = 0;
                    if (rc[j]) ok = 0;
                    rr = rc[j] = 1;
                    count++;
                }
                printf("%c", board[i][j]);
            }
            printf("\n");
        }

        if (ok && count == 8) return "Correct";
        else return "Incorrect";
    }
};

int main () {
    vector<string> board;
    char temp[9];
    
    for (int i = 0; i < 8; i++) {
        scanf(" %s", temp);
        board.push_back(temp);
    }

    cout << EightRooks::isCorrect(board);
}
