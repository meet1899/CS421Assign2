#include "randomcspgen.h"

int main(){
    int n;
    float alpha, p, r;
    cout << "Enter Number of Variables n: ";
    cin >> n;
    cout << "Enter constraint tightness p (0<p<1): ";
    cin >> p;
    cout << "Enter value of alpha: ";
    cin >> alpha;
    cout << "Enter value of r: ";
    cin >> r;

    vector<int> Variables = genVariables(n);
    //printV(Variables);
    unordered_map<int, vector<int>> Domains = genDommains(n, alpha, Variables);
    //printum(Domains);

/*
    vector<int> V1 = {1,2};
    vector<int> V2 = {3,4};
    vector<vector<int>> Var;
    Var.push_back((V1));
    cout<<endl;
    for(int i=0; i<Var.size(); ++i){
        printV(Var[i]);
        cout<<endl;
    }
*/
    map< pair<int, int>, vector<pair<int,int> > > constrain = genconstrains(n, p, r, alpha, Variables, Domains);
    printm(constrain);



    return 0;
}