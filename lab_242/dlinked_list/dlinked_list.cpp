#include <iostream>

template <class T>
class DLinkedList {
public:
    class Node; // Forward declaration
protected:
    Node* head;
    Node* tail;
    int count;
public:
    DLinkedList();
    ~DLinkedList();
    void    add(const T &e);
    void    add(int index, const T &e);
    int     size();
    bool    empty();
    T       get(int index);
    void    set(int index, const T &e);
    int     indexOf(const T &item);
    bool    contains(const T &item); 
    T       removeAt(int index);
    bool    removeItem(const T &item);
    void    clear();
public:
    class Node
    {
    private:
        T data;
        Node *next;
        Node *previous;
        friend class DLinkedList<T>;

    public:
        Node()
        {
            this->previous = NULL;
            this->next = NULL;
        }

        Node(const T &data)
        {
            this->data = data;
            this->previous = NULL;
            this->next = NULL;
        }
    };

};

template <class T>
void DLinkedList<T>::add(const T& e) {
    /* Insert an element into the end of the list. */
    this->add(this->count, e);
}

template<class T>
void DLinkedList<T>::add(int index, const T& e) {
    /* Insert an element into the list at given index. */ 
    if (index < 0 || index > this->count) {
        throw std::out_of_range("Index out of range!");
    }
    typedef DLinkedList<T>::Node DNode;
    DNode* newNode = new DNode(e);
    if (index == 0) {
        //* prepend
        if (!this->head) {
            this->head = this->tail = newNode;
        }
        newNode->next = this->head;
        this->head->previous = newNode;
        this->head = newNode;
    }
    else if (index == count) {
        //* append
        this->tail->next = newNode;
        newNode->previous = this->tail;
        this->tail = newNode;
    }
    else {
        //* standard case
        int i = 0;
        DNode* walker = this->head;
        while (i < index) {
            i++;
            walker = walker->next;
        }
        newNode->next = walker;
        newNode->previous = walker->previous;
        walker->previous = newNode;
        newNode->previous->next = newNode;
    }
    this->count++;
}

template<class T>
int DLinkedList<T>::size() {
    /* Return the length (size) of list */ 
    return this->count;
}

template<class T>
T DLinkedList<T>::get(int index) {
    /* Give the data of the element at given index in the list. */
    if (index < 0 || index >= this->count) {
        throw std::out_of_range("Index out of range!");
    }
    int i = 0;
    DLinkedList<T>::Node* walker = this->head;
    while (i < index) {
        walker = walker->next;
        i++;
    }
    return walker->data;
}

template <class T>
void DLinkedList<T>::set(int index, const T& e) {
    /* Assign new value for element at given index in the list */
    if (index < 0 || index >= this->count) {
        throw std::out_of_range("Index out of range!");
    }
    int i = 0;
    DLinkedList<T>::Node* walker = this->head;
    while (i < index) {
        walker = walker->next;
        i++;
    }
    walker->data = e;
}

template<class T>
bool DLinkedList<T>::empty() {
    /* Check if the list is empty or not. */
    return this->count == 0;
}

template<class T>
int DLinkedList<T>::indexOf(const T& item) {
    /* Return the first index wheter item appears in list, otherwise return -1 */
    typename DLinkedList<T>::Node* walker = this->head;
    int idx = 0;
    while (walker) {
        if (walker->data == item) {
            return idx;
        }
        walker = walker->next;
        idx++;
    }
    return -1;
}

template<class T>
bool DLinkedList<T>::contains(const T& item) {
    /* Check if item appears in the list */
    return (this->indexOf(item) != -1);
}

template <class T>
T DLinkedList<T>::removeAt(int index) {
    /* Remove element at index and return removed value */
    if (index < 0 || index >= this->count) {
        throw std::out_of_range("Index out of range!");
    }
    DLinkedList<T>::Node* tempNode;
    if (index == 0) {
        tempNode = this->head;
        this->head = this->head->next;
        if (!this->head) {
            this->tail = nullptr;
        }
        else {
            this->head->previous = nullptr;
            tempNode->next = nullptr;
        }
    }
    else if (index == this->count - 1) {
        tempNode = this->tail;
        this->tail = this->tail->previous;
        this->tail->next = nullptr;
        tempNode->previous = nullptr;
    }
    else {
        int i = 0;
        DLinkedList<T>::Node* walker = this->head;
        while (i < index) {
            walker = walker->next;
            i++;
        }
        walker->previous->next = walker->next;
        walker->next->previous = walker->previous;
        walker->next = walker->previous = nullptr;
        tempNode = walker;
    }
    T tempValue = tempNode->data;
    delete tempNode;
    this->count--;
    return tempValue;
}

template <class T>
bool DLinkedList<T>::removeItem(const T& item)
{
    /* Remove the first apperance of item in list and return true, otherwise return false */
    int index = this->indexOf(item);
    if (index == -1) {
        return false;
    }
    else {
        this->removeAt(index);
        return true;
    }
}

template<class T>
void DLinkedList<T>::clear(){
    /* Remove all elements in list */
    while (this->head->next) {
        this->head = this->head->next;
        delete this->head->previous;
        this->head->previous = nullptr;
    }
    delete this->head;
    this->head = this->tail = nullptr;
    this->count = 0;
}


struct ListNode {
    int val;
    ListNode *left;
    ListNode *right;
    ListNode(int x = 0, ListNode *l = nullptr, ListNode* r = nullptr) : val(x), left(l), right(r) {}
};

ListNode* reverse(ListNode* head, int a, int b) {
    if (!head || a == b) return head;
    
    ListNode* dummy = new ListNode(0); // Dummy node to handle edge cases
    dummy->right = head;
    head->left = dummy;
    
    // Find node at position (a-1)
    ListNode* before = dummy;
    for (int i = 1; i < a; i++) {
        before = before->right;
    }
    
    // reHead is the node at position 'a'
    ListNode* reHead = before->right;
    
    // Reverse nodes from position a to b
    ListNode* current = reHead;
    ListNode* prev = before;
    ListNode* next = nullptr;
    
    for (int i = a; i <= b; i++) {
        next = current->right;
        current->right = prev;
        current->left = next;
        prev = current;
        current = next;
    }
    
    // Reconnect the reversed portion
    before->right = prev;
    prev->left = before;
    reHead->right = current;
    if (current) current->left = reHead;
    
    // Update head if necessary
    ListNode* newHead = dummy->right;
    newHead->left = nullptr;
    delete dummy;
    
    return newHead;
}