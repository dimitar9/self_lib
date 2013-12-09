#include "objectValue.h"
#include <iostream>
#include <string>
using namespace std;
int main(){
    NameObject<int> no1("Smallest Prime number", 2);
    NameObject<int> no2(no1);
    NameObject<int> no3("bad egg",99);
    cout << no1.nameValue<<endl;
    cout << no1.objectValue<<endl;
    
    cout << no2.nameValue<<endl;
    cout << no2.objectValue<<endl;
    no1 = no3;

    cout << no1.nameValue<<endl;
    cout << no1.objectValue<<endl;
    
    return 0;
}
