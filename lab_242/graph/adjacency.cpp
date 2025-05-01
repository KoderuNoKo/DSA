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
        Adjacency* result = new Adjacency;
        bool* visited = new bool[this->V];



        // clean up
        delete[] visited;
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
        Adjacency* result = new Adjacency;
        bool* visited = new bool[this->V];
        list<int> buffer;
        
        // start at v
        visited[v] = true;
        buffer.push_front(v);
        
        // BFS
        while(!buffer.empty()) {
            // visit current vertex
            int curr = buffer.back();
            buffer.pop_back();
            result->push(curr);
            // push next vertices
            for (int i = 0; i < this->adj[curr].getSize(); i++) {
                int next = this->adj[curr].getElement(i);
                if (!visited[next]) {
                    buffer.push_front(next);
                    visited[next] = true;
                }
            }
        }

        delete[] visited;
        return result;
	}

	void DFSRec(int v, Adjacency* result, bool* visited)
	{
	    if (v == this->V || visited[v]) {
	        return;
	    }
	    // visit current vertex
	    visited[v] = true;
	    result->push(v);
        // DFS
	    for (int i = 0; i < this->adj[v].getSize(); i++) {
	        this->DFSRec(adj[v].getElement(i), result, visited);
	    }
	}
	
	Adjacency *DFS(int v)
    {
        // v is a vertex we start DFS
        Adjacency* result = new Adjacency;
        bool* visited = new bool[this->V];
        for (int i = 0; i < this->V; i++) {
            visited[i] = false;
        }
        this->DFSRec(v, result, visited);
        delete[] visited;
        return result;
	}

    //Heling functions
    void topoHelp(int v, list<bool>& visited, list<int>& stack)
    {
        // set current v as visited
        list<bool>::iterator it = visited.begin();
        advance(it, v);
        *it = true;

        for (int i = 0; i < this->adj[v].getSize(); i++) {
            int vertex = this->adj[v].getElement(i);
            it = visited.begin();
            advance(it, vertex);
            if (!*it) {
                this->topoHelp(vertex, visited, stack);
            }
        }
        stack.push_front(v);
    }
    
    void topologicalSort(){
        //TODO
        list<int> stack;
        list<bool> visited(this->V, false);

        for (int i = 0; i < this->V; i++) {
            // get an unvisited node
            list<bool>::iterator it = visited.begin();
            advance(it, i);
            if (!*it) {
                this->topoHelp(i, visited, stack);
            }
        }

        for (int vertex : stack) {
            cout << vertex << " ";
        }
    }
};

