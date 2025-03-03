#include "randomcspgen.h"

int main(){
    cout << "Enter Number of Variables and alpha : ";
    int n;
    float alpha;
    cin >> n;
    cin >> alpha;
    vector<int> Variables = genVariables(n);
    printV(Variables);
    unordered_map<int, vector<int>> Domains = genDommains(n, alpha, Variables);
    printum(Domains);


    vector<int> V1 = {1,2};
    vector<int> V2 = {3,4};
    vector<vector<int>> Var;
    Var.push_back((V1));
    cout<<endl;
    for(int i=0; i<Var.size(); ++i){
        printV(Var[i]);
        cout<<endl;
    }
    

    return 0;
}