#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
#include <random>

using namespace std;

vector<int> generate_csp(int n, double p, double alpha, double r) {
    // STEP 0
    // Compute variables of the CSP
    vector<int> variables(n);
    for (int i = 0; i < n; ++i) {
        variables[i] = i;
    }
    
    // Compute domain of each variable
    int d = round(pow(n, alpha)); // domain size of each variable
    unordered_map<int, vector<int>> domains;
    for (int var : variables) {
        vector<int> domain(d);
        for (int i = 0; i < d; ++i) {
            domain[i] = i;
        }
        domains[var] = domain;
    }
-
    // STEP 1
    // Compute quantity of constrains
    int constrains_qnt = round(r * n * log(n));
    vector<pair<int, int>> var_constrains;
    unordered_set<string> unique_pairs;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, n - 1);

    while (var_constrains.size() <= constrains_qnt) {
        int var1 = dis(gen);
        int var2 = dis(gen);
        // make sure we select a new unique pair of variables
        if (var1 != var2) {
            string pair_key = to_string(var1) + "," + to_string(var2);
            string reverse_key = to_string(var2) + "," + to_string(var1);
            if (unique_pairs.find(pair_key) == unique_pairs.end() && unique_pairs.find(reverse_key) == unique_pairs.end()) {
                var_constrains.emplace_back(var1, var2);
                unique_pairs.insert(pair_key);
            }
        }
    }

    // STEP 2
    // Compute quantity of incompatible pairs of values
    int incomp_qnt = round(p * (pow(d, 2)));
    unordered_map<pair<int, int>, vector<pair<int, int>>, hash<pair<int, int>>> constrains;

    // For each constrain
    for (const auto& [var1, var2] : var_constrains) {
        vector<pair<int, int>> incomp_values;
        unordered_set<string> unique_incomp_pairs;

        while (incomp_values.size() <= incomp_qnt) {
            int val1 = domains[var1][dis(gen) % d];
            int val2 = domains[var2][dis(gen) % d];
            // make sure we select a new unique pair of variables
            string incomp_key = to_string(val1) + "," + to_string(val2);
            string reverse_incomp_key = to_string(val2) + "," + to_string(val1);
            if (unique_incomp_pairs.find(incomp_key) == unique_incomp_pairs.end() && unique_incomp_pairs.find(reverse_incomp_key) == unique_incomp_pairs.end()) {
                incomp_values.emplace_back(val1, val2);
                unique_incomp_pairs.insert(incomp_key);
            }
        }
        constrains[{var1, var2}] = incomp_values;
    }

    // Return full CSP
    return {variables, domains, constrains};
}
