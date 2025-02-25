class LinkedList {
    public: 
        class Node;
    private:
        Node* head;
        Node* tail;
        int size;
    public: 
        class Node {
            private: 
                int value;
                Node* next;
                friend class LinkedList;
            public:
                Node() {
                    this->next = nullptr;
                }
                Node(Node* node) {
                    this->value = node->value;
                    this->next = node->next;
                }
                Node(int value, Node* next = nullptr) {
                    this->value = value;
                    this->next = next;
                }
        };
        LinkedList(): head(nullptr), tail(nullptr), size(0) {};
	void partition(int k);
};

void LinkedList::partition(int k) 
{
    Node* result  = new Node(1);    // final result
    Node* smaller = new Node(1);    // tail ptr for add to each partition
    Node* equal   = new Node(1);
    Node* larger  = new Node(1);
    Node* heads   = smaller;        // partition heads
    Node* heade   = equal;
    Node* headl   = larger;
    Node* cursor  = head;           // ptr for traversal

    while (cursor) {
        if (cursor->value < k) {
            smaller->next = cursor;
            smaller = cursor;
        }
        else if (cursor->value == k) {
            equal->next = cursor;
            equal = cursor;
        }
        else {
            larger->next = cursor;
            larger = cursor;
        }
        cursor = cursor->next;
    }
    smaller->next = equal->next = larger->next = nullptr;

    // build result
    cursor = result;
    if (smaller != heads) {
        result->next = heads->next;
        result = smaller;
        this->tail = smaller;
    }
    if (equal != heade) {
        result->next = heade->next;
        result = equal;
        this->tail = equal;
    }
    if (larger != headl) {
        result->next = headl->next;
        this->tail = larger;
    }
    result = cursor->next;

    // delete dummy nodes
    cursor->next = heads->next = heade->next = headl->next = nullptr;
    delete cursor;
    delete heads;
    delete heade;
    delete headl;
    
    this->head = result;
}