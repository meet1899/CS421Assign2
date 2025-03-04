#include <iostream>
#include <string>

using namespace std;

int main(){
    string X = "X";
    int i = 1;
    X += to_string(i);
    cout << X << endl;

    return 0;
}