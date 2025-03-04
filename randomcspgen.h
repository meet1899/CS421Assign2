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

void printV(vector<int> &v) {
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
}

void printum(unordered_map<int, vector<int>> um){
    for(auto it = um.begin(); it != um.end(); it++){
        cout << it->first << " : " ;
        vector<int> v = it->second;
        printV(v);
        cout << endl;
    }
}

void print_pair(pair<int, int> pair){
    cout << "("<<pair.first << " : " << pair.second << "), ";
}

void print_vpair(vector<pair<int,int> > vp){
    for (int i = 0; i < vp.size(); i++){
        print_pair(vp[i]);
    }
}

void printm(map< pair<int, int>, vector<pair<int,int> > > m){
    for (auto& p : m){
        print_pair(p.first);
        cout << " :: ";
        print_vpair(p.second);
        cout<< "\n";
    }

}

int random_vec(vector<int> vec){
    int randomIndex = rand() % vec.size();

    return vec[randomIndex];
}

bool find(pair<int, int> a, vector<pair<int, int>> b){

    bool c;
    int key =a.first;
    auto it = find_if(
        b.begin(), b.end(),
        [key](const auto& p) { return p.first == key; });


    if (it!=b.end())
        c = true;
    else
        c = false;

    bool e;
    key =a.second;
    auto its = find_if(
        b.begin(), b.end(),
        [key](const auto& p) { return p.second == key; });


    if (its!=b.end() && its == it)
        e = true;
    else
        e = false;
        
    return c&&e;
}

vector<int> genVariables(int n){
    vector<int> V;
    for(int i= 0; i < n; ++i){
        V.push_back(i);
    }
    return V;
}

unordered_map<int, vector<int>> genDommains(int n, float alpha, vector<int> V){
    int d = round(pow(n,alpha));
    unordered_map<int, vector<int>> Domains;
    for(int i=0; i < V.size(); ++i){
        vector<int> dom;
        for(int j=0; j < d; ++j){
            dom.push_back(j);
        }
        Domains.insert({V[i],dom});
    }
    return Domains;
}

int domain_size(int n, float alpha){
    int d = round(pow(n,alpha));
    return d;
}

map< pair<int, int>, vector<pair<int,int> > > genconstrains(int n, float p, float r, float alpha, vector<int> V, unordered_map<int, vector<int>> Domains, int &conquan, int &incomquan){
    
    conquan = round(r * n * log(n));
    vector< pair<int,int> > var_constrains;
    
    while(var_constrains.size() != conquan){
        int var1 = random_vec(V);
        int var2 = random_vec(V);
        pair<int, int> check = {var1,var2};
        pair<int, int> checknew = {var2,var1};
        if(var1 != var2 && !find(check, var_constrains) && !find(checknew, var_constrains)){
            var_constrains.push_back(check) ;
        }
    }
    int d = round(pow(n,alpha));
    incomquan = round( p * pow(d,2));
    map< pair<int, int>, vector<pair<int,int> > > constrains;

    for(auto var : var_constrains){
        vector< pair<int,int> > incomval;
        
        while(incomval.size() < incomquan ){
            int val1 = random_vec(Domains[var.first]);
            int val2 = random_vec(Domains[var.second]);
            pair<int, int> check = {val1,val2};
            pair<int, int> checknew = {val2,val1};
            if(!find(check, incomval) || !find(checknew, incomval)){
                incomval.push_back(check);
            }
        }
            
        constrains[var] = incomval;
    }

    return constrains;
}