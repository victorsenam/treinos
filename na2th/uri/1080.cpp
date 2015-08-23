#include <iostream>

using namespace std;

int main()
{
    int number,
        highest=0,
        hpos = 0,
        pos = 1;
    while(cin >> number)
    {
        if(number >= highest)
        {
            highest=number;
            hpos = pos;
        }
        pos++;
    }
    cout << highest << endl << hpos <<endl;
}
