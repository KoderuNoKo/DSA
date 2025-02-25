#include<iostream>

using namespace std;

template <class T>
class SLinkedList {
public:
    class Node; // Forward declaration
protected:
    Node* head;
    Node* tail;
    int count;
public:
    SLinkedList(): head(NULL), tail(NULL), count(0);
    ~SLinkedList() { };
    void    add(const T& e);
    void    add(int index, const T& e);
    int     size();
    void    clear();
    bool    empty();
    T       get(int index);
    void    set(int index, const T& e);
    int     indexOf(const T& item);
    bool    contains(const T& item);
    T       removeAt(int index);
    bool    removeItem(const T& item);
public:
    class Node {
    private:
        T data;
        Node* next;
        friend class SLinkedList<T>;
    public:
        Node() {
            next = 0;
        }
        Node(Node* next) {
            this->next = next;
        }
        Node(T data, Node* next = NULL) {
            this->data = data;
            this->next = next;
        }
    };
};

template <class T>
void SLinkedList<T>::add(const T& e) {
    /* Insert an element into the end of the list. */
    Node* newNode = new Node(e);
    if (!this->head) {
        this->head = this->tail = newNode;
    }
    else {
        this->tail->next = newNode;
        this->tail = newNode;
    }
    this->count++;
}

template<class T>
void SLinkedList<T>::add(int index, const T& e) {
    /* Insert an element into the list at given index. */ 
    if (index >= count) {
        this->add(e);
        return;
    }
    Node* newNode = new Node(e);
    if (index == 0) {
        newNode->next = this->head;
        this->head = newNode;
        this->count++;
        return;
    }
    int i = 0;
    Node* itr = this->head;
    while (i < index - 1) {
        itr = itr->next;
        i++;
    }
    newNode->next = itr->next;
    itr->next = newNode;
    this->count++;
}

template<class T>
int SLinkedList<T>::size() {
    /* Return the length (size) of list */ 
    return this->count;
}

template<class T>
T SLinkedList<T>::get(int index) {
    /* Give the data of the element at given index in the list. */
    Node* itr = this->head;
    int i = 0;
    while (i < index && itr) {
        itr = itr->next;
        i++;
    }
    if (itr) {
        return itr->data;
    }
    else {
        throw std::out_of_range("index is out of range!");
    }
}

template <class T>
void SLinkedList<T>::set(int index, const T& e) {
    /* Assign new value for element at given index in the list */
    Node* itr = this->head;
    int i = 0;
    while (i < index && itr) {
        itr = itr->next;
        i++;
    }
    if (itr) {
        itr->data = e;
    }
    else {
        throw std::out_of_range("index is out of range!");
    }
}

template<class T>
bool SLinkedList<T>::empty() {
    /* Check if the list is empty or not. */
    return (this->count == 0);
}

template<class T>
int SLinkedList<T>::indexOf(const T& item) {
    /* Return the first index wheter item appears in list, otherwise return -1 */
    Node* itr = this->head;
    int idx = 0;
    while (itr) {
        if (itr->data == item) {
            return idx;
        }
        itr = itr->next;
        idx++;
    }
    return -1;
}

template<class T>
bool SLinkedList<T>::contains(const T& item) {
    /* Check if item appears in the list */
    Node* itr = this->head;
    while (itr) {
        if (itr->data == item) {
            return true;
        }
        itr = itr->next;
    }
    return false;
}

template <class T>
T SLinkedList<T>::removeAt(int index)
{
    /* Remove element at index and return removed value */

    // case invalid index
    if (index >= this->count || index < 0) {
        throw std::out_of_range("index is out of range!");
    }

    // case update both head and tail
    if (this->count == 1) {
        T item = this->head->data;
        delete this->head;
        this->head = this->tail = nullptr;
        this->count--;
        return item;
    }

    Node* temp = this->head;
    T tempData = temp->data;

    // case update just head
    if (index == 0) {
        this->head = this->head->next;
        delete temp;
        this->count--;
        return tempData;
    }

    // case update just tail
    if (index == this->count - 1) {
        // move to before tail
        int i = 0;
        while(i < index - 1) {
            temp = temp->next;
            i++;
        }
        // remove & update tail
        this->tail = temp;
        temp = this->tail->next;
        this->tail->next = nullptr;
        tempData = temp->data;
        delete temp;
        this->count--;
        return tempData;
    }

    // normal case
    int i = 0;
    while(i < index - 1) {
        temp = temp->next;
        i++;
    }

    Node* remove = temp->next;
    temp->next = temp->next->next;
    tempData = remove->data;
    delete remove;
    this->count--;
    return tempData;
}

template <class T>
bool SLinkedList<T>::removeItem(const T& item)
{
    /* Remove the first apperance of item in list and return true, otherwise return false */
    int idx = this->indexOf(item);
    if (idx == -1) {
        return false;
    }
    this->removeAt(idx);
    return true;
}

template<class T>
void SLinkedList<T>::clear(){
    /* Remove all elements in list */
    Node* del = this->head;
    while(this->head) {
        del = this->head;
        this->head = this->head->next;
        delete del;
    }
    this->head = this->tail = nullptr;
    this->count = 0;
}