#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

void test(int &a)
{
    a = 2;
}

int main(void)
{
    int a = 1;
    test(a);
    cout << "Voici la valeur de A " << a << endl; 
    return 0;
}