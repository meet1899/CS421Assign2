#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <cmath>
#include <random>
#include <algorithm>
#include <bits/stdc++.h>
#include "randomcspgen.h"

using namespace std;

vector< pair<int, int> > BT_sol(vector<int> Variables, unordered_map<int, vector<int>> Domains,map< pair<int, int>, vector<pair<int,int> > > constrains){
    vector< pair<int,int> > assignments;
    int una_var=99;
    for(auto var : Variables){
        for(auto assigned : assignments){
            if(var != assigned.first ){
                una_var = var;
            }
            else{
                break;
            }
        }
    }
    
    vector<int> una_var_domain;
    for(auto domain : Domains){
        if(una_var == domain.first){
            una_var_domain = domain.second;
        }
    }

    for(auto val : una_var_domain ){
        
    }




}