#include "randomcspgen.h"
#include "strategies.h"

int main(){
    int n;
    float alpha, p, r;
    cout << "Input parameter: "<<endl;
    cout << "Number of Variables (n): ";
    cin >> n;
    cout << "Constraint tightness (p): ";
    cin >> p;
    cout << "Constant alpha: ";
    cin >> alpha;
    cout << "Constant r: ";
    cin >> r;
    cout<<endl;

    cout<< "Generated RB Instance" << endl;
    int Domain_size = domain_size(n, alpha);
    cout << "Domain Size: " << Domain_size<< endl << endl;
    
    vector<int> Variables = genVariables(n);
    
    unordered_map<int, vector<int>> Domains = genDommains(n, alpha, Variables);
    
    int conquan,incomquan;
    map< pair<int, int>, vector<pair<int,int> > > constrain = genconstrains(n, p, r, alpha, Variables, Domains, conquan, incomquan);
    
    cout << "Number of constraints: " << conquan <<endl<< endl;
    
    cout << "Number of incompatible tuples: " << incomquan <<endl<< endl;

    cout << "Variables: ";
    printV(Variables);
    cout<<endl;

    cout << "Domains: " <<endl;
    printum(Domains);
    cout<<endl;

    cout << "Constrains: "<<endl;
    printm(constrain);
    cout<<endl;

    vector< pair<int,int> > assignments;

    assignments = BT_sol(Variables, Domains, constrain, assignments);

    printa(assignments);

    return 0;
}