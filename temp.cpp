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
