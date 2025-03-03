#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <cmath>
#include <random>
#include <algorithm>

using namespace std;

void printV(vector<int> &v) {
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
}

void printum(unordered_map<int, vector<int>> um){
    for(auto it = um.begin(); it != um.end(); it++){
        cout << it->first << ": " ;
        vector<int> v = it->second;
        printV(v);
        cout << endl;
    }
        
}

int random_vec(vector<int> vec){
    int randomIndex = rand() % vec.size();

    return vec[randomIndex];
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

map< vector<int>, vector<int> > genconstrains(int n, float p, float r, float alpha, vector<int> V, unordered_map<int, vector<int>> Domains){
    
    int conquan = round(r * n * log(n));
    unordered_map<int, vector<int>> var_constrains;
    

    return ;
}