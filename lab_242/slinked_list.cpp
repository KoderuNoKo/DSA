template<class T>
void SLinkedList<T>::add(int index, const T& e) {
    /* Insert an element into the list at given index. */ 
    
    Node* newNode = new Node(e); 
    if (index == 0){
        newNode->next = head; 
        head = newNode; 
    } else {
        Node* temp = head; 
        for (int i = 0; i < index - 1; i++){
            temp = temp->next;
        }
        newNode->next = temp->next; 
        temp->next = newNode; 
    }
    count++;
}