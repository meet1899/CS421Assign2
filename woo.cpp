#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

void change(unordered_map<int, vector<int>> &a){
    int c = 0;
    int d = 3;
    int b = 1;

    for (auto i : a) {
        vector<int> sec =i.second;
        if(i.first == b){
            for (int j = 0; j < i.second.size(); j++) {
                if(i.second[j] == d){
                    sec[j] = c;
                    a[b] = sec;
                }
            }
        }
    }
}

void printV(vector<int> &v) {
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
}

int main(){
    string X = "X";
    int i = 1;
    X += to_string(i);
    cout << X << endl;

    unordered_map<int, vector<int>> a = {{2, {1,2,3,4}}, {1, {1,2,3,4}}};

    change(a);

    for (auto i : a) {
        cout << i.first << ": ";
        printV(i.second);
        cout<<endl;
    }

    return 0;
}