#include "BankManager.h" 
#include <iostream>

using namespace std;

int main() {
    
    BankManager atm_system_manager;
    atm_system_manager.run();
    cout << "Program terminated. Goodbye." << endl;
    
    return 0;
}