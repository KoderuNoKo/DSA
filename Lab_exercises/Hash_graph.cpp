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

    void topoRec(int root, bool* visited, stack<int>& result) {
        visited[root] = true;

        for (int i = 0; i < adj[root].getSize(); i++) {
            int neighbor = adj[root].getElement(i);
            if (!visited[neighbor]) {
                topoRec(neighbor, visited, result);
            }
        }

        // Push the current vertex to the result stack after visiting all neighbors
        result.push(root);
    }

    // Topological Sort function
    void topologicalSort() {
        bool* visited = new bool[V];
        for (int i = 0; i < V; i++) {
            visited[i] = false;
        }
        
        stack<int> result;

        // Traverse each vertex in the graph
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                topoRec(i, visited, result);
            }
        }

        // Print the topological order
        while (!result.empty()) {
            cout << result.top() << " ";
            result.pop();
        }
    }
};

int connectedComponents(std::vector<std::vector<int>>& edges) {
    std::vector<bool> visited(edges.size(), false);
    int noConnected = 0;
    
    for (size_t root = 0; root < edges.size(); ++root) {
        if (!visited[root]) {
            // perform BFS on the graph starting at the root
            std::queue<int> travs;
            travs.push(root);
            visited[root] = true;
            while (!travs.empty()) {
                int curr = travs.front();
                travs.pop();
                for (int item : edges[curr]) {
                    if (!visited[item]) {
                        visited[item] = true;
                        travs.push(item);
                    }
                }
            }
            // traversal on one component complete, increase count
            noConnected++;
        }
    }
    return noConnected;
}

int foldShift(long long key, int addressSize)
{
	string keyStr = to_string(key);
	int res = 0;
	size_t i = 0;
	for (; i < keyStr.length() - addressSize; i += addressSize)
	{
		res += stol(keyStr.substr(i, addressSize));
	}
	res += stol(keyStr.substr(i));
	res %= (int)pow(10, addressSize);
	return res;
}

int rotation(long long key, int addressSize)
{
	string keyStr = to_string(key);
	char last = keyStr[keyStr.size() - 1];
	keyStr.pop_back();
	keyStr.insert(keyStr.begin(), last);

	return foldShift(stol(keyStr), addressSize);
}

// câu 6
class FriendGroups {
public:
    FriendGroups(const std::vector<std::vector<int>>& friends) {
        graph = friends;
        visited.assign(friends.size(), false);
    }

    int countFriendGroups() {
        int count = 0;
        for (size_t i = 0; i < graph.size(); i++) {
            if (!visited[i]) {
                dfs(i);
                count++;
            }
        }
        return count;
    }

private:
    std::vector<std::vector<int>> graph;
    std::vector<bool> visited;

    void dfs(int u) {
        visited[u] = true;
        for (int v : graph[u]) {
            if (!visited[v]) {
                dfs(v);
            }
        }
    }
};

int numberOfFriendGroups(vector<vector<int>>& friends) {
    FriendGroups fg(friends);
    return fg.countFriendGroups();
}

// hết câu 6 cmnr
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
	
	bool isCyclicUtil(int v, vector<bool>& visited, vector<bool>& inPath)
    {
        visited[v] = true;
        inPath[v] = true;
        
        for (int neighbor : adj[v]) {
            if (!visited[neighbor]) {
                if (isCyclicUtil(neighbor, visited, inPath)) {
                    return true;
                }
            }
            else if (inPath[neighbor]) {
                return true;
            }
        }
        
        inPath[v] = false;
        return false;
    }
    
    bool isCyclic()
    {
        vector<bool> visited(V, false);
        vector<bool> inPath(V, false);
        
        for (int i = 0; i < V; i++) {
            if (!visited[i] && isCyclicUtil(i, visited, inPath)) {
                return true;
            }
        }
        
        return false;
    }
}; 

long int midSquare(long int seed)
{
    long int square = seed * seed;
    long int midsquare = (square / 100);
    midsquare %= 10000;
    return midsquare;
}
long int moduloDivision(long int seed, long int mod)
{
    return seed % mod;
}
long int digitExtraction(long int seed, int* extractDigits, int size)
{
	string seedstr = to_string(seed);
	string extracted = "";
	for (int i = 0; i < size; i++) {
		extracted.push_back(seedstr[extractDigits[i]]);
	}
	return stol(extracted);
}

int pairMatching(std::vector<int>& nums, int target) {
    std::unordered_map<int, int> numFrequency;
    int countPairs = 0;

    for (int num : nums) {
        int complement = target - num;
        
        // Check if the complement exists in the map and has a non-zero frequency
        if (numFrequency.find(complement) != numFrequency.end() && numFrequency[complement] > 0) {
            countPairs++;
            // Reduce the frequency of the complement to indicate it's used in a pair
            numFrequency[complement]--;
        } else {
            // Increment the frequency of the current number
            numFrequency[num]++;
        }
    }

    return countPairs;
}

