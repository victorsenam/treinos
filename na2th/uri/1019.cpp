#include <iostream>

using namespace std;

int main()
{
    int seconds, interval = 3600;

    cin >> seconds;

    while( interval > 0 )
    {
        cout << seconds/interval;
        seconds %= interval;
        (interval != 1)? cout << ":" : cout << endl ;
        interval /= 60;
    }

}
