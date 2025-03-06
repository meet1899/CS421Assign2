#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <cmath>
#include <random>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

int find_value(int var, vector< pair<int,int> > assignments){
    int return_val = -999;
    for(auto assigns : assignments){
        if(assigns.first == var){
            return_val = assigns.second;
        }
    }
    return return_val;
}

bool check_vio(int val, int var, vector<int> Variables, vector< pair<int,int> > assignments, map< pair<int, int>, vector<pair<int,int> > > constraints){
                
    bool viol = false;

    for(auto var_const: constraints){
        pair<int,int> var_pair = var_const.first;
        if(var_pair.first == var){
            int var2 = var_pair.second;
            int val_var2 = find_value( var2, assignments);
            if(val_var2 >= 0){
                pair<int,int> p1 = {val, val_var2};
                pair<int,int> p2 = {val_var2, val};

                for(auto constraint : constraints){
                    if(constraint.first == var_pair ){
                        vector<pair<int,int> > checkpair_const = constraint.second;
                        for(auto p : checkpair_const){
                            if(p1 == p || p2 == p){
                                viol = true;
                            }
                        }
                    }
                }
            }

        }
        else if(var_pair.second == var){
            int var2 = var_pair.first;
            int val_var2 = find_value( var2, assignments);
            if(val_var2 >= 0){
                pair<int,int> p1 = {val, val_var2};
                pair<int,int> p2 = {val_var2, val};

                for(auto constraint : constraints){
                    if(constraint.first == var_pair ){
                        vector<pair<int,int> > checkpair_const = constraint.second;
                        for(auto p : checkpair_const){
                            if(p1 == p || p2 == p){
                                viol = true;
                            }
                        }
                    }
                }
            }

        }
    }
    return viol;
}

int select_unasvar(vector< pair<int,int> > assignments, vector<int> Variables){
    //select a variable that is unassigned
    int una_var = -99;
    for(auto var : Variables){
        for(auto assigned : assignments){
            if(var != assigned.first ){
                una_var = var;
            }
        }
    }
    return una_var;
}

vector<int> una_domain(int una_var, unordered_map<int, vector<int>> Domains){
    //get the domain of new unassigned variable
    vector<int> una_var_domain;
    for(auto domain : Domains){
        if(una_var == domain.first){
            una_var_domain = domain.second;
        }
    }
    return una_var_domain;
}

void change_domain(int una_var, int sol_val, unordered_map<int, vector<int>> &Domains){

    vector<int> sec = Domains[una_var];
    sec.erase(find(sec.begin(), sec.end(), sol_val));

}

void printa( vector< pair<int,int> > a){
    for(auto i : a){
        cout << "("<<i.first << " : " << i.second << "), ";
    }
}

vector< pair<int, int> > BT_sol(vector<int> Variables, unordered_map<int, vector<int>> Domains,map< pair<int, int>, vector<pair<int,int> > > constraints, vector< pair<int,int> > assignments){
    cout<<"z"<<endl;
    if(assignments.size() == Variables.size()){
        cout<<"y"<<endl;
        return assignments;
    }
        
    cout << "a" <<endl;
    int una_var= select_unasvar(assignments, Variables);
    cout << "b" <<endl;
    vector<int> una_var_domain = una_domain(una_var, Domains);    
    cout << "c" <<endl;
    for(auto val : una_var_domain ){
        cout << "x" <<endl;
        int sol_val = val;
        cout << "d" <<endl;
        bool violation = check_vio(sol_val, una_var, Variables, assignments, constraints);
        cout << "e" <<endl;
        if(!violation){
            cout << "f" <<endl;
            pair<int,int> sol = {una_var, sol_val};
            assignments.push_back(sol);
        }
        cout << "g" <<endl;
        change_domain(una_var, sol_val, Domains);
        cout << "h" <<endl;
        BT_sol(Variables, Domains, constraints, assignments);
        cout << "i" <<endl;
    }
    
}