class Graph {

   private:

         int nover;

         string* labels;

         int** wm; // weight matrix

   public:

        Graph(string vertices[],const int n):noverKhông,labels(vertices) {

               wm = new int[n][n];

                for (int i = 0; i < n; i++) 

                     for (int j = 0; j < n; j++) 

                         if (i == j) wm[i][i] = 0; else wm[i][j] = INT_MAX;

        }

       void addEdge(struct edge edges[],int n) { 
for(int i=0;i<n;i++){
    for(int j=0;j<nover;j++){
        if(edges[i].src==labels[j]){
            for(int o=0;o<nover;o++){
                if(edges[i].dst==labels[o]){
                    wm[j][o]=edges[i].weight;
                    break;
                }
            }
        }
    }
}
       }
};

class GEdge {

      string label; // label of the destination vertex of the edge

      int weight; // weight of the edge

      GEdge(string l,int w) { label=l;weight=w;}

};

and the declaration of the adjacent list implementation of a weighted undirected graph as follows

class Graph {

   private:

         int nover;

         Link<GEdge>* srclst; // list of source vertex of edges

   public:

        Graph(string vertices[], int n):noverKhông {

                srclst = new Link<GEdge>[n];

                for (int i = 0; i < n; i++) srclst[i].element.label = vertices[i];

        }

       void addEdge(struct edge edges[],int n) {
for (int i = 0; i < n; i++) {
    for (int j = 0; j < nover; j++) {
        if (edges[i].ver1 == srclst[j].element.label) {
            GEdge cc(edges[i].ver2, edges[i].weight);
            Link<GEdge>* temp = new Link<GEdge>(cc, nullptr);
            Link<GEdge>* t = &srclst[j];
            while (!(!t->next || t->next->element.label > edges[i].ver2)) {
                t = t->next;
            }
            temp->next = t->next;
            t->next = temp;
        }
        if (edges[i].ver2 == srclst[j].element.label) {
            GEdge cc(edges[i].ver1, edges[i].weight);
            Link<GEdge>* temp = new Link<GEdge>(cc, nullptr);
            Link<GEdge>* t = &srclst[j];
            while (!(!t->next || t->next->element.label > edges[i].ver1)) {
                t = t->next;
            }
            temp->next = t->next;
            t->next = temp;
        }
    }
}
      }
};

class GEdge {

      int idx; // index of the destination vertex of the edge

      int weight; // weight of the edge

      GEdge(int l,int w): idx(l),weight(w){}

};

and the declaration of the adjacent list implementation of a weighted undirected graph as follows

class Graph {

   private:

         int nover;

         string * labels;

         Link<GEdge>* srclst; // list of source vertex of edges

   public:

        Graph(string vertices[], int n):nover(n),labels(vertices) {

                srclst = new Link<GEdge>[n];

        }
void BFS(string startlabel,void (Graph::*action)(int))
{
    bool* visited = new bool[nover];
    for (int i = 0; i < nover; i++) {
        visited[i] = false;
    }
    
    LQueue< Link<GEdge>* > q;
    q.enqueue(&srclst[startlabel[0] - 'a']);
    visited[startlabel[0] - 'a'] = true;
    
    while (q.length() != 0) 
    {
        Link<GEdge>* curr = q.frontValue();
        q.dequeue();
        
        (this->*action)(curr - srclst);
        
        curr = curr->next;
        while (curr) {
            if (!visited[curr->element.idx]) {
                visited[curr->element.idx] = true;
                q.enqueue(&srclst[curr->element.idx]);
            }
            curr = curr->next;
        }
    }
}
};
