class GEdge {

      int idx; // index of the destination vertex of the edge

      int weight; // weight of the edge

      GEdge(string l,int w) { label=l;weight=w;}

};

and the declaration of the adjacent list implementation of a weighted undirected graph as follows

class Graph {

   private:

         int nover;

         string * labels;

         Link<GEdge>* srclst; // list of source vertex of edges

   public:

        Graph(string vertices[], int n):noverNo,labels(vertices) {

                srclst = new Link<GEdge>[n];

        }

};

void topologicalSort(void (Graph::*action)(int)) 
{
    int* counter = new int[nover];
    bool* visited = new bool[nover];
    for (int i = 0; i < nover; i++)
    {
        Link<GEdge>* curr = srclst[i].next;
        visited[i] = false;
        while (curr) {
            counter[curr->element.idx]++;
            curr = curr->next;
        }
    }
    
    LQueue<Link<GEdge>*> q;
    for (int i = 0; i < nover; i++)
    {
        if (counter[i] == 0) {
            q.enqueue(&srclst[i]);
            visited[i] = true;
            break;
        }
    }
    
    while (q.length() != 0)
    {
        Link<GEdge>* curr = q.frontValue();
        q.dequeue();
        
        (this->*action)(curr - srclst);
        
        curr = curr->next;
        while (curr) {
            counter[curr->element.idx]--;
            curr = curr->next;
        }
        
        for (int i = 0; i < nover; i++)
        {
            if (visited[i] || (counter[i] != 0)) {
                continue;
            }
            q.enqueue(&srclst[i]);
            visited[i] = true;
        }
    }
    delete[] counter;
    delete[] visited;
}
