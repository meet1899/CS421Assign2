#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <algorithm>
#include <variant>

using namespace std;

// revise function
// --------------------------
bool revise(vector<int>& Di, vector<int>& Dj, string Xi, string Xj, const set<pair<int, int>>& constrain_Xi_Xj) {

  bool revised = false;
  // Iterate over Di using an iterator so that removal is safe
  for (auto it = Di.begin(); it != Di.end(); ) {
    bool is_all_incompatible = true;
    for (auto y : Dj) {
      // Check if the pair (x,y) is in constrain_Xi_Xj
      if (constrain_Xi_Xj.find(make_pair(*it, y)) == constrain_Xi_Xj.end()) {
        is_all_incompatible = false;
        break;
      }
    }
    if (is_all_incompatible) {
      it = Di.erase(it);
      revised = true;
    }
    else {
      ++it;
    }
  }
  return revised;
}

// neighbors function
// --------------------------
vector<string> neighbors(const string& node, const vector<pair<string, string>>& arcs, const string& except_node) {

  vector<string> neighbors;
  for (auto arc : arcs) {
    // If node is present in arc
    if (arc.first == node || arc.second == node) {
      // For each member in arc, add if conditions are met
      if ((arc.first != node) && (arc.first != except_node)) {
        if (find(neighbors.begin(), neighbors.end(), arc.first) == neighbors.end()) {
          neighbors.push_back(arc.first);
        }
      }
      if ((arc.second != node) && (arc.second != except_node)) {
        if (find(neighbors.begin(), neighbors.end(), arc.second) == neighbors.end()) {
          neighbors.push_back(arc.second);
        }
      }
    }
  }
  return neighbors;
}

// arc_consistency function
// --------------------------
bool arc_consistency(const vector<string>& variables, map<string, vector<int>>& domains, const map<pair<string, string>, set<pair<int, int>>>& constrains) {

  vector<pair<string, string>> arcs;
  // Create a list of arcs from the keys of constrains
  for (auto p : constrains) {
    arcs.push_back(p.first);
  }

  if (arcs.size() > 0) {

    vector<pair<string, string>> queue;
    queue.push_back(arcs[0]);

    while (!queue.empty()) {
      pair<string, string> arc = queue.back();
      queue.pop_back();
      string Xi = arc.first;
      string Xj = arc.second;
      // Check if the constraint exists for (Xi, Xj)
      auto it_constraint = constrains.find(make_pair(Xi, Xj));
      if (it_constraint != constrains.end()) {
        if (revise(domains[Xi], domains[Xj], Xi, Xj, it_constraint->second)) {
          if (domains[Xi].empty()) {
            return false;
          }
          vector<string> neighbors_Xi = neighbors(Xi, arcs, Xj);
          for (auto Xk : neighbors_Xi) {
            if (find(arcs.begin(), arcs.end(), make_pair(Xk, Xi)) != arcs.end()) {
              queue.push_back(make_pair(Xk, Xi));
            }
            else {
              queue.push_back(make_pair(Xi, Xk));
            }
          }
        }
      }
    }
  }
  return true;
}

// Backtrack Search Implementation
// --------------------------
// In this part, Backtrack Search and all of its needed utility functions are implemented.

// select_unassigned_variable function
// --------------------------
string select_unassigned_variable(const vector<string>& variables, const map<string, vector<int>>& domains, const map<pair<string, string>, set<pair<int, int>>>& constrains, const map<string, int>& assignment, string heuristic = "") {

  // non_assigned_vars = [v for v in variables if not v in assignment.keys()]
  for (auto v : variables) {
    if (assignment.find(v) == assignment.end()) {
      return v;
    }
  }
  return "";
}

// order_domain_values function
// --------------------------
vector<int> order_domain_values(const string& var, const map<string, int>& assignment, const vector<string>& variables, const map<string, vector<int>>& domains, const map<pair<string, string>, set<pair<int, int>>>& constrains) {

  return domains.at(var);
}

// Struct to represent inference result
struct InferenceResult {
  bool failure;
  map<string, int> assignments;
};

// inference function
// --------------------------
InferenceResult inference(const string& var, int value, const vector<string>& variables, map<string, vector<int>>& domains, const map<pair<string, string>, set<pair<int, int>>>& constrains, const map<string, int>& assignment, const string& inf_type = "") {

  InferenceResult new_assignments;
  new_assignments.failure = false;
  new_assignments.assignments = map<string, int>(); // empty

  if (inf_type == "FC") {
    bool result = arc_consistency(variables, domains, constrains);
    if (!result) {
      new_assignments.failure = true; // "Failure"
    }
  }
  else if (inf_type == "MAC") {
    // Find variables that are unassigned and neighbor of var
    vector<string> unassg_vars;
    map<pair<string, string>, set<pair<int, int>>> sub_constrains;
    for (auto p : constrains) {
      string var1 = p.first.first;
      string var2 = p.first.second;
      if (var == var1 || var == var2) {
        string other_var = "";
        if (var1 == var) {
          other_var = var1;
        }
        else {
          other_var = var2;
        }
        if (assignment.find(other_var) == assignment.end()) {
          unassg_vars.push_back(other_var);
          sub_constrains[make_pair(var1, var2)] = p.second;
        }
      }
    }
    // Call AC with the sub constrains and variables
    bool result = arc_consistency(unassg_vars, domains, sub_constrains);
    if (!result) {
      new_assignments.failure = true; // "Failure"
    }
  }

  return new_assignments;
}

// is_consistent function
// --------------------------
bool is_consistent(const string& var, int value, const map<string, int>& assignment, const map<pair<string, string>, set<pair<int, int>>>& constrains) {

  bool is_consistent = true;
  for (auto p : assignment) {
    string var1 = p.first;
    // Check if (var1,var) in constrains
    if (constrains.find(make_pair(var1, var)) != constrains.end()) {
      if (constrains.at(make_pair(var1, var)).find(make_pair(p.second, value)) != constrains.at(make_pair(var1, var)).end()) {
        is_consistent = false;
      }
    }
    else if (constrains.find(make_pair(var, var1)) != constrains.end()) {
      if (constrains.at(make_pair(var, var1)).find(make_pair(value, p.second)) != constrains.at(make_pair(var, var1)).end()) {
        is_consistent = false;
      }
    }
  }
  return is_consistent;
}

// Define a variant type for backtracking result
using BacktrackResult = variant<map<string, int>, string>;

// backtrack function
// --------------------------
BacktrackResult backtrack(map<string, int>& assignment, const vector<string>& variables, map<string, vector<int>>& domains, const map<pair<string, string>, set<pair<int, int>>>& constrains, const string& inf_type = "") {

  // If assignment is complete
  if (assignment.size() == variables.size()) {
    return assignment;
  }
  // Select unassigned variable
  string var = select_unassigned_variable(variables, domains, constrains, assignment);
  for (int value : order_domain_values(var, assignment, variables, domains, constrains)) {
    InferenceResult inference_assignments;
    // If value is consistent with assignment
    if (is_consistent(var, value, assignment, constrains)) {
      // Add new assignment
      assignment[var] = value;
      // Make a copy of domains, in case the branch is backtracked
      map<string, vector<int>> _domain = domains;
      // Perform inference (Forward Checking or MAC)
      inference_assignments = inference(var, value, variables, _domain, constrains, assignment, inf_type);
      if (!inference_assignments.failure) {
        // Add inference to assignment
        for (auto p : inference_assignments.assignments) {
          assignment[p.first] = p.second;
        }
        // Recursive call for next layer in the backtrack search tree
        BacktrackResult result = backtrack(assignment, variables, domains, constrains, inf_type);
        if (holds_alternative<map<string, int>>(result)) {
          return result;
        }
      }
    }
    // Remove var from assignment if the branch fails
    assignment.erase(var);
  }
  return string("Failure");
}

// Example main function to demonstrate usage
int main() {
  // Example variables and domains (customize as needed)
  vector<string> variables = {"X", "Y"};
  map<string, vector<int>> domains;
  domains["X"] = {1, 2, 3};
  domains["Y"] = {1, 2, 3};

  // Example constrains:
  // The key is a pair of variables,
  // the value is a set of incompatible pairs of domain values.
  map<pair<string, string>, set<pair<int, int>>> constrains;
  // For example, constraint between X and Y: (1,1) and (2,2) are incompatible.
  constrains[make_pair("X", "Y")] = {make_pair(1, 1), make_pair(2, 2)};

  // Start with an empty assignment
  map<string, int> assignment;

  // Call backtrack search with no inference type (or "FC"/"MAC")
  BacktrackResult result = backtrack(assignment, variables, domains, constrains, "FC");

  if (holds_alternative<map<string, int>>(result)) {
    cout << "Solution found:" << endl;
    map<string, int> sol = get<map<string, int>>(result);
    for (auto p : sol) {
      cout << p.first << " = " << p.second << endl;
    }
  } else {
    cout << "Failure" << endl;
  }
  
  return 0;
}
