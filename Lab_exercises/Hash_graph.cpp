#include <iostream>
#include <list>
using namespace std;

class Adjacency
{
private:
	list<int> adjList;
	int size;
public:
	Adjacency() {}
	Adjacency(int V) {}
	void push(int data)
	{
		adjList.push_back(data);
		size++;
	}
	void print()
	{
		for (auto const &i : adjList)
			cout << " -> " << i;
	}
	void printArray()
	{
		for (auto const &i : adjList)
			cout << i << " ";
	}
	int getSize() { return adjList.size(); }
	int getElement(int idx) 
	{
		auto it = adjList.begin();
		advance(it, idx);
		return *it;
	}
};

class Graph
{
private:
	int V;
	Adjacency *adj;

public:
	Graph(int V)
	{
		this->V = V;
		adj = new Adjacency[V];
	}
	
	void addEdge(int v, int w)
	{
		adj[v].push(w);
		adj[w].push(v);
	}
	
    void printGraph()
	{
		for (int v = 0; v < V; ++v)
		{
			cout << "\nAdjacency list of vertex " << v << "\nhead ";
			adj[v].print();
		}
	}
	
	Adjacency *BFS(int v)
    {
        // v is a vertex we start BFS
        Adjacency* ret = new Adjacency;
        
        bool* visited = new bool[this->V];
        for (int i = 0; i < this->V; i++) {
            visited[i] = false;
        }
        
        list<int> travq;
        travq.push_back(v);
        visited[v] = true;
        
        while (travq.size() != 0) 
        {
            // pop and traverse the vertex at the front of the queue
            int curr = travq.front();
            travq.pop_front();
            ret->push(curr);
            
            // push new vertices into the queue
            for (int i = 0; i < adj[curr].getSize(); i++)
            {
                int newVer = adj[curr].getElement(i);   // vertex to be added
                
                if (!visited[newVer]) {                 // if vertex is not visited, add it into the queue
                    travq.push_back(newVer);
                    visited[newVer] = true;
                }
            }
        }
        return ret;
	}
};

int connectedComponents(vector<vector<int>>& edges) {
    // STUDENT ANSWER
    vector<bool> visited(edges.size(), false);
    int noVisited = 1;
    int noConnected = 0;
    
    while (1) 
    {
        // find the root to start traversing in the next component
        size_t root = 0;
        while (visited[root] && root < edges.size()) {
            root++;
        }
        
        // if all vertices are visited, then stop
        if (root == edges.size()) {     
            break;
        }
        
        // perform BFS on the graph start at the root
        stack<int> travs;
        travs.push(root);
        visited[root] = true;
        while (!travs.empty())
        {
            int curr = travs.top();
            travs.pop();
            for (int item : edges[curr]) {
                if (!visited[item]) {
                    visited[item] = true;
                    noVisited++;
                }
            }
        }
        
        // traverse on one component complete, increase count
        noConnected++;
    }
    return noConnected;
}
