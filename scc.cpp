#include <iostream>
#include <vector>
#include <sstream>       // std::istringstream
#include <string>        // std::string
using namespace std;

int V;                   // The number of the states
                         // (= the number of the vertices in the state-transiton graph)
vector<string> states;   // The states.
vector<vector<int> > G;  // The state-transition graph represented in an adjency list.
vector<vector<int> > rG; // The edge-reversed graph of the above.
vector<int> vs;          // The vertices in the post-order of the result of the DFS.
vector<bool> isVisited;  // The flag used for the DFS search
                         //   (keeps if it is already visited or not)
vector<int> tpl_order;   // The topological order of the SCCs.
                         // If the states belongs to the same SCC,
                         // then they have the same index.

void readStates() {
  while (1) {
    string s;
    getline(cin, s);      // Read the state id and the state from the standard input.
    if (s == "") return;  // Return if finished reading the states
    states.push_back(s);
  }
}

void readTransitions() {
  string dummy;
  getline(cin, dummy);            // Read the 'init:1'
  
  while (1) {                     
    string s;
    getline(cin, s);              // Read transitions. e.g. '1::2, 3'
    if (s == "") return;          // Return if finished reading the states
    istringstream is(s);          // Convert the string to istringstream
                                  // to parse transitions from it.
    int from; 		       	  
    is >> from;                   // Read the index of the 'from' state.
    is.ignore(2);                 // Ignore the '::'.
    while(1) {		       	  
      int to; 		       	  
      is >> to;                   // Read the index of the 'to' state.
      if (is.fail()) break;	  // Break if finished reading all the 'to' states.
      is.ignore(1);               // Ignore the ','.
      G[from - 1].push_back(to - 1);
         // Add the outgoing edge from the 'from' state to the 'to' state.
         // Notice that you should subtract 1 from the index of the states  
         // since the index of the states in the slim starts from 1.
         // (not 0).
      rG[to - 1].push_back(from - 1);
    }
  }
}

void dfs(const int v) { // The Depth First Search
  // 'v' is the (index of the) vertex.

  isVisited[v] = true;
  for (int i = 0; i < (int)G[v].size(); i++ ) {
    // 'G[v]' represent the outgoing edges of the vertex 'v'.
    // 'G[v][i]' is 'v's i-th outgoing edge.

    // In cpp, the size of the vector is returned in the 'size_type' type.
    // Therefore, you must cast the type to 'int' (if you want to compare it with int).

    if (!isVisited[G[v][i]]) // If the outgoing edge is not already visited, 
      dfs(G[v][i]);          // then try traversing from its head (vertex).
  }

  vs.push_back(v);           // push back the vertex (in the post-order).
}

void rdfs(const int v, const int k) { // The Reversed DFS.
  // 'v' is the vertex and 'k' is the (topological) order of the SCC.
  
  isVisited[v] = true;
  tpl_order[v] = k;
  for (int i = 0; i < (int)rG[v].size(); i++ ) {
    if (!isVisited[rG[v][i]])
      rdfs(rG[v][i], k);  // The reachable vertices (in DFS) are in the same order 'k'.
  }
}

int scc() { // Apply DFS and the reversed DFS.
            // returns the number of the SCCs.

  fill(isVisited.begin(), isVisited.end(), false);
  // clear the 'isVisited' vector (initialize the all elements to false).

  vs.clear(); // Initialize the vector with size 0.

  // The first DFS
  for (int v = 0; v < V; v++ ) {
    if(!isVisited[v]) dfs(v);
  }

  fill(isVisited.begin(), isVisited.end(), false);
  // clear the 'isVisited' vector (initialize the all elements to false).

  int k = 0;
  // The second DFS (the DFS with the reversed edges)
  // Notice the search starts from the last vertex
  // (the vertex lastly visited in the first DFS).
  for (int i = V - 1; i >= 0; i-- ) {
    if (!isVisited[vs[i]]) {
      rdfs(vs[i], k);
      k++;  // If there is no more reachable vertices, they are in the same SCC,
            // and you should increase 'k' (= the (topological) order)
            // for the next SCCs to represent that they belong to the different SCC.
    }
  }
  return k; // The number of the SCCs.
}

int main() {
  string dummy;
  getline(cin, dummy);    // Read the string 'States'
  readStates();
  V = states.size(); // The number of the states.
  
  cout << "The states (just showing for debugging purpose only) " << endl;
  cout << "<the index of the state> : "
       << "<the state slim printed (including 1 added index)>" << endl; 
  for(int k = 0; k < V; k++ ) {
    cout << k << " : " << states[k] << endl; 
  }

  getline(cin, dummy); // Read the string 'Transitions'
  
  // Initialize the size of the vectors
  // (to the number of the states (= vertices in the state-transition graph)).
  G.resize(V);
  rG.resize(V);
  tpl_order.resize(V);
  isVisited.resize(V);

  readTransitions(); // Read transition graph.

  cout << "The input graph (just showing for debugging purpose only)" << endl;
  for (int v = 0; v < V; v++ ) {
    for (int e = 0; e < (int)G[v].size(); e++ ) {
      cout << v << " -> " << G[v][e] << endl;
    }
  }

  // Apply the Tarjan's algorithm.
  cout << "The number of the SCCs is " << scc() << "." << endl;

  cout << "The topological order of each vertices are" << endl;
  for (int v = 0; v < V; v++ ) {
    cout << v << ": " << tpl_order[v] << endl;
  }

  return 0;
}
