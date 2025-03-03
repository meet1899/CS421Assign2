#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <sstream>
#include <chrono>
#include <algorithm>
using namespace std;

// Structure to hold the generated CSP components
struct CSP {
  vector<int> variables;
  vector<vector<int>> domains;
  map< pair<int, int>, vector< pair<int, int> > > constrains;
};

// Dummy implementation of generate_csp
// This function generates variables, domains, and constraints based on input constants.
CSP generate_csp(int n, double p, double alpha, double r) {
  CSP csp;
  // Generate variables: 0, 1, 2, ..., n-1
  for (int i = 0; i < n; i++) {
    csp.variables.push_back(i);
  }
  
  // Generate domains: For simplicity, each variable gets the same domain.
  // Here, we generate a domain with elements 0, 1, ..., n-1.
  // (Note: The sample output shows a different ordering, but we follow a simple ordering.)
  vector<int> domain;
  for (int i = 0; i < n; i++) {
    domain.push_back(i);
  }
  // Add the same domain for each variable.
  for (int i = 0; i < n; i++) {
    csp.domains.push_back(domain);
  }
  
  // Generate dummy constraints:
  // For each consecutive pair of variables, we add a constraint with one dummy pair.
  for (int i = 0; i < n - 1; i++) {
    vector< pair<int, int> > cons_list;
    cons_list.push_back(make_pair(i, i+1));
    csp.constrains[make_pair(i, i+1)] = cons_list;
  }
  
  return csp;
}

// Dummy implementation of arc_consistency
// This function pretends to perform arc-consistency and returns true.
bool arc_consistency(const vector<int>& variables, const vector<vector<int>>& domains,
                     const map< pair<int, int>, vector< pair<int, int> > >& constrains) {
  // Dummy implementation always returns true.
  return true;
}

// Dummy implementation of backtrack search algorithm.
// The inf_type parameter is used to select the type of inference used ("", "FC", or "MAC").
// This simple implementation assigns the first available value from the domain for each variable.
map<int, int> backtrack(map<int, int> assignment, const vector<int>& variables,
                         const vector<vector<int>>& domains,
                         const map< pair<int, int>, vector< pair<int, int> > >& constrains,
                         const string inf_type = "") {
  // If assignment is complete, return it.
  if (assignment.size() == variables.size()) {
    return assignment;
  }
  
  // Find an unassigned variable. Here, simply choose the first not in assignment.
  int var = -1;
  for (auto v : variables) {
    if (assignment.find(v) == assignment.end()) {
      var = v;
      break;
    }
  }
  
  // For each value in the domain for this variable
  for (auto val : domains[var]) {
    // Add the value to the assignment
    assignment[var] = val;
    // In a full implementation, we would check consistency and possibly perform inference.
    // Here we simply continue recursively.
    map<int, int> result = backtrack(assignment, variables, domains, constrains, inf_type);
    if (!result.empty() && result.size() == variables.size()) {
      return result;
    }
    // Remove the assignment if not successful
    assignment.erase(var);
  }
  // If no value leads to a solution, return empty assignment.
  return map<int, int>();
}

// main function
//
// AUTHOR
// ---------
// Jhonatan S. Oliveira
// oliveira@uregina.ca
// Department of Computer Science
// University of Regina
// Canada
//
//
// DESCRIPTION
// -----------
// This script is a utility for running all implemented search algorithms.
// After calling the script in a prompt command, the user can input constants and pick a search algorithm.
// For more details, please, see documentation in the README file.
int main() {
  // The Python main() function starts here.
  /*
  Description
  -----------
  Shows a menu to the user.
  User can input constants used by the model RB.
  User can pick a search algorithm for solving the CSP.
  See README file for more details.
  
  Example
  -------
  >>> main()
  >>> Initial state (comma separated):
  --> 1,2,3,8,5,6,7,4,0
  >>> Choose the Search algorithm
  >>> 1) Depth First
  >>> 2) Breath First
  >>> 3) Best First - tiles out of place
  >>> 4) Best First - min moves
  >>> 5) Best First - heuristic H
  --> 3
  >>> Result:
  [[1, 2, 3, 8, 5, 6, 7, 4, 0], [1, 2, 3, 8, 5, 0, 7, 4, 6], [1, 2, 3, 8, 0, 5, 7, 4, 6], [1, 2, 3, 8, 5, 6, 7, 0, 4], [1, 2, 0, 8, 5, 3, 7, 4, 6], [1, 2, 3, 8, 0, 6, 7, 5, 4], [1, 2, 3, 8, 4, 5, 7, 0, 6], [1, 0, 3, 8, 2, 5, 7, 4, 6], [1, 2, 3, 0, 8, 5, 7, 4, 6], [1, 2, 3, 8, 5, 6, 0, 7, 4], [1, 2, 3, 8, 4, 5, 7, 6, 0], [1, 2, 3, 8, 6, 0, 7, 5, 4], [1, 0, 2, 8, 5, 3, 7, 4, 6], [1, 0, 3, 8, 2, 6, 7, 5, 4], [1, 2, 3, 0, 8, 6, 7, 5, 4], [1, 2, 3, 8, 4, 5, 0, 7, 6], [1, 2, 3, 8, 4, 0, 7, 6, 5], [1, 2, 3, 8, 0, 4, 7, 6, 5]]
  >>> Want to try again? (Y/N)
  -->
  */
  
  bool keep_running = true;
  
  while (keep_running) {
    // Input constants
    cout << endl;
    cout << endl;
    cout << ">>> !!! Starting Assignment 3 Solution !!! <<<" << endl;
    cout << endl;
    cout << ">>> Constants:" << endl;
    cout << "--> Number of variables (n): ";
    int n;
    cin >> n;
    cout << "--> Constraint Tightness (p): ";
    double p;
    cin >> p;
    cout << "--> Constant alpha: ";
    double alpha;
    cin >> alpha;
    cout << "--> Constant r: ";
    double r;
    cin >> r;
    cout << endl;
    
    // Using AC or not
    cout << endl;
    cout << ">>> Do you wish to run Arc-Consistency before backtrack?" << endl;
    cout << "--> (y/n): ";
    string use_ac_str;
    cin >> use_ac_str;
    cout << endl;
    bool use_ac = false;
    if (use_ac_str == "y" || use_ac_str == "Y" || use_ac_str == "yes" || use_ac_str == "Yes" || use_ac_str == "YES") {
      use_ac = true;
    }
    
    // Shows options
    cout << endl;
    cout << ">>> Choose the Search algorithm" << endl;
    cout << ">>> 1) Backtrack Search" << endl;
    cout << ">>> 2) Backtrack Search with Forward Checking" << endl;
    cout << ">>> 3) Backtrack Search with Maintaining Arc Consistency (MAC)" << endl;
    
    // Input search algorithm option
    cout << "--> ";
    string option;
    cin >> option;
    cout << endl;
    
    // Generate CSP and run AC if needed
    CSP csp = generate_csp(n, p, alpha, r);
    bool ac_result = true;
    if (use_ac) {
      ac_result = arc_consistency(csp.variables, csp.domains, csp.constrains);
    }
    
    // Print generated CSP
    cout << endl;
    cout << ">>> Generated CSP:" << endl;
    
    // Print Variables
    cout << ">>> Variables: ";
    // Create a list of variable names in the form "X"+ value
    for (size_t i = 0; i < csp.variables.size(); i++) {
      cout << "X" << csp.variables[i];
      if (i != csp.variables.size() - 1) {
        cout << ",";
      }
    }
    cout << endl;
    
    // Print Domain based on the first variable's domain
    cout << ">>> Domain: ";
    if (!csp.domains.empty() && !csp.domains[0].empty()) {
      for (size_t i = 0; i < csp.domains[0].size(); i++) {
        cout << csp.domains[0][i];
        if (i != csp.domains[0].size() - 1) {
          cout << ",";
        }
      }
    }
    cout << endl;
    
    // Print Constrains:
    cout << ">>> Constrains:" << endl;
    for (auto &entry : csp.constrains) {
      int var1 = entry.first.first;
      int var2 = entry.first.second;
      cout << "(" << var1 << "," << var2 << "): ";
      for (size_t i = 0; i < entry.second.size(); i++) {
        int val1 = entry.second[i].first;
        int val2 = entry.second[i].second;
        cout << to_string(val1) + "," + to_string(val2);
        if (i != entry.second.size() - 1) {
          cout << " ";
        }
      }
      cout << endl;
    }
    cout << endl;
    
    // If AC can not reduce domain to zero or AC is not run.
    auto tic = chrono::high_resolution_clock::now();
    if (ac_result) {
      // Run search algorithm
      map<int, int> result;
      if (option == "1") {
        result = backtrack(map<int, int>(), csp.variables, csp.domains, csp.constrains);
      } else if (option == "2") {
        result = backtrack(map<int, int>(), csp.variables, csp.domains, csp.constrains, "FC");
      } else if (option == "3") {
        result = backtrack(map<int, int>(), csp.variables, csp.domains, csp.constrains, "MAC");
      }
      // Shows result from search algorithm
      if (!result.empty()) {
        cout << ">>> Solution <<<" << endl;
        // Print assignment in the form "Xv:val"
        bool first = true;
        for (auto &pair_entry : result) {
          if (!first) {
            cout << ", ";
          }
          cout << "X" << pair_entry.first << ":" << pair_entry.second;
          first = false;
        }
        cout << endl;
        cout << endl;
      } else {
        cout << ">>> Not a valid choice." << endl;
      }
    }
    // In case AC returns fail.
    else {
      cout << ">>> You are lucky! Just by running AC we can tell that the CSP has no solution." << endl;
    }
    auto tac = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = tac - tic;
    // Loop again if users wants to 
    cout << ">>> Solution computed in " << elapsed.count() << " (s)" << endl;
    cout << ">>> Want to try again? (Y/N)" << endl;
    cout << "--> ";
    string again;
    cin >> again;
    
    if (again != "y" && again != "Y") {
      keep_running = false;
    }
  }
  
  return 0;
}
// Run main
// (In C++ the main function is executed by default)
  
