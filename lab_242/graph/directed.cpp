#include <iostream>
#include <vector>
#include <list>
using namespace std;

class DirectedGraph 
{ 
	int V;
	vector<list<int>> adj;
public:
	DirectedGraph(int V)
	{
		this->V = V; 
		adj = vector<list<int>>(V, list<int>());
	}
	void addEdge(int v, int w)
	{
		adj[v].push_back(w);
	}
	bool isCyclic()
	{
	    // Student answer
	    vector<bool> visited(this->V, false);
	    vector<bool> recStack(this->V, false);
	    for (int i = 0; i < this->V; i++) {
	        if (!visited[i] && this->isCyclicUtil(i, visited, recStack)) {
	            return true;
	        }
	    }
	    return false;
	}
	bool isCyclicUtil(int u, vector<bool>& visited, vector<bool>& recStack) {
	    visited[u] = true;
	    recStack[u] = true;
	    for (int i : this->adj[u]) {
	        if (!visited[i] && this->isCyclicUtil(i, visited, recStack)) {
	            return true;
	        }
	        else if (recStack[i]) {
	            return true;
	        }
	    }
	    return recStack[u] = false;
	}
}; 