#include <iostream>     /* File: initializer1.cpp */
using namespace std;	

int main()	
{
    int w = 3.4;
    int x1 {6};
    int x2 = {8};       // = here is optional
    int y {'k'};
      // Error!d

    cout << "w = " << w << endl;
    cout << "x1 = " << x1 << endl << "x2 = " << x2 << endl;


    int& ww = w;
    int& www {ww}; www =123;
    cout << "www = " << www << endl;
    return 0;
}
