#include <iostream>
#include <string>

using namespace std;

template <class T>
class DGraph {
public:
     class VertexNode; // Forward declaration
     class Edge; // Forward declaration
protected:
     VertexNode* nodeList; //list of vertexNode of DGraph
     int countVertex;
     int countEdge;
public:
     DGraph() {
          this->nodeList = nullptr;
          this->countEdge = 0;
          this->countVertex = 0;
     }
     ~DGraph() {};
     VertexNode* getVertexNode(T vertex);
     void add(T vertex);
 
     void connect(T from, T to, float weight=0);
 
     void removeVertex(T removeVertex);
     bool removeEdge(T from, T to);
     string shape();
     bool empty();
     void clear();
     void printGraph();

public:
     class VertexNode {
     private:
          T vertex;
          Edge* adList; //list of adjacent edge of this vertex
          VertexNode* next;

          friend class Edge;
          friend class DGraph;
     public:

        VertexNode(T vertex, Edge* adList = nullptr, VertexNode* next = nullptr) {
            this->vertex = vertex;
            this->adList = adList;
            this->next = next;
        }
          string toString();
          void addAdjacentEdge(Edge* newEdge);
          bool connectTo(VertexNode* toNode, float weight = 0);
          bool removeTo(VertexNode* toNode);
          Edge* getEdge(VertexNode* toNode);
     };
 
     class Edge {
     private:
          VertexNode* fromNode;
          VertexNode* toNode;
          float weight;
          Edge* next;

          friend class VertexNode;
          friend class DGraph;
     public:
          Edge(VertexNode* fromNode, VertexNode* toNode, float weight = 0.0, Edge* next = nullptr) {
               this->fromNode = fromNode;
               this->toNode = toNode;
               this->weight = weight;
               this->next = next;
          }
          string toString();

     };
};


template<class T>
typename DGraph<T>::Edge* DGraph<T>::VertexNode::getEdge(VertexNode* toNode) {
    //TODO: Iterate through the adjacency list of this vertex
    //      checking if there exists an edge with this vertex as the starting vertex 
    //      and "toNode" as the ending vertex. 
    //      If not return nullptr, else return that edge.
    DGraph<T>::Edge* walker = this->adList;
    while (walker && walker->toNode != toNode) {
        walker = walker->next;
    }
    return walker;
}

template<class T>
void DGraph<T>::VertexNode::addAdjacentEdge(Edge* newEdge) {
    //TODO: add newEdge to adjacency list of this vertex.
    newEdge->next = this->adList;
    this->adList = newEdge;
}

template<class T>
bool DGraph<T>::VertexNode::connectTo(VertexNode* toNode, float weight) {
    //TODO: get edge from this node to "toNode".
    DGraph<T>::Edge* edge = this->getEdge(toNode);
    //TODO: If the edge is not existed, create a new Edge and add it to the adjacency list. 
    //      If the edge is existed, update its weight.
    if (edge) {
        edge->weight = weight;
        return false;
    }
    else {
        this->adList = new Edge(this, toNode, weight, this->adList);
        return true;
    }
    //TODO: Return true if a new Edge is created; otherwise, return false.
}

template<class T>
bool DGraph<T>::VertexNode::removeTo(VertexNode *toNode) {
    //TODO: remove the edge with "toNode" as the ending vertex from this node's adjacency list.
    DGraph<T>::Edge* removeEdge = this->adList;
    DGraph<T>::Edge* beforeRemove = nullptr;
    
    while (removeEdge && removeEdge->toNode != toNode) {
        beforeRemove = removeEdge;
        removeEdge = removeEdge->next;
    }
    //TODO: return true if success; otherwise, return false.
    
    if (removeEdge) {
        // found edge to be removed
        if (beforeRemove) {
            beforeRemove->next = removeEdge->next;   
        }
        delete removeEdge;
        return true;
    }
    else {
        return false;
    }
}

template <class T>
bool DGraph<T>::removeEdge(T from, T to) {
    //TODO: get vertexNode with "from" and vertexNode with "to".
    DGraph<T>::VertexNode* fromNode = this->nodeList;
    while (fromNode && fromNode->vertex != from) {
        fromNode = fromNode->next;
    }
    DGraph<T>::VertexNode* toNode = this->nodeList;
    while (toNode && toNode->vertex != to) {
        toNode = toNode->next;
    }
    //TODO: If either of the two vertexNode objects does not exist, 
    //      throw an exception: VertexNotFoundException("Vertex doesn't exist!").
    if (!fromNode || !toNode) {
        throw VertexNotFoundException("Vertex doesn't exist!");
    }
    //TODO: Delete the edge between the "from" vertexNode and the "to" vertexNode. (use removeTo method)
    //      If success return true and decrement the countEdge; otherwise, return false;
    if (fromNode->removeTo(toNode)) {
        this->countEdge--;
        return true;
    }
    return false;
}

template <class T>
void DGraph<T>::removeVertex(T removeVertex) {
    //TODO: get vertexNode with "removeVertex"
    DGraph<T>::VertexNode* removeNode = this->nodeList;
    while (removeNode && removeNode->vertex != removeVertex) {
        removeNode = removeNode->next;
    }
    //TODO: If this vertexNode isn't existed,
    //      throw an exception: VertexNotFoundException("Vertex doesn't exist!").
    if (!removeNode) {
        throw VertexNotFoundException("Vertex doesn't exist!");
    }
    //TODO: Iterate through all the vertexNode in the graph's Node list. For each vertexNode:
    //      - Check for an edge from the current vertex to the "removeVertex". 
    //      If such an edge exists, delete it (use removeTo method) and decrement the countEdge.
    //      - Check for an edge from the "removeVertex" to the current vertex. 
    //      If such an edge exists, delete it (use removeTo method) and decrement the countEdge. 
    DGraph<T>::VertexNode* walker = this->nodeList;
    while(walker) {
        this->countEdge -= (walker->removeTo(removeNode)) ? 1 : 0;
        this->countEdge -= (removeNode->removeTo(walker)) ? 1 : 0;
        walker = walker->next;
    }
    //TODO: Delete the vertexNode containing removeVertex from the Node list of the graph
    //      Decrement the countVertex.
    walker = this->nodeList;
    DGraph<T>::VertexNode* prev = nullptr;
    while(walker != removeNode) {
        prev = walker;
        walker = walker->next;
    }
    if (prev) {
        prev->next = walker->next;
    }
    this->countVertex--;
    delete walker;
}

template<class T>
string DGraph<T>::shape() {
    //TODO: return the string with format: [Vertices: <numOfVertex>, Edges: <numOfEdge>]
    stringstream ss;
    ss << "[Vertices: " << this->countVertex << ", Edges: " << this->countEdge << "]";
    return ss.str();
}

template<class T>
bool DGraph<T>::empty() {
    //TODO: return if graph is empty (it doesn't have any vertex and edge)
    return this->countVertex == 0 && this->countEdge == 0;
}

template<class T>
void DGraph<T>::clear() {
    //TODO: remove all edges and vertices of graph.
    while (this->nodeList) {
        this->removeVertex(this->nodeList->vertex);
    }
    this->countVertex = 0;
    this->countEdge = 0;
}
