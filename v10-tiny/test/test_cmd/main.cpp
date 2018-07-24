#include <iostream>
#include "test.h"
using namespace std;

int main()
{
    Test t;
    cout << "Hello World!" << endl;
    while(1){
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    return 0;
}

