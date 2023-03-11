#include <iostream>
using namespace std;

int *f()
{
    int a = 0;
    return (&a);
}


int main()
{
   f();
}