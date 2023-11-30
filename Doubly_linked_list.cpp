#include <iostream>
template <class T>
class DLinkedList
{
public:
    class Iterator; //forward declaration
    class Node;     //forward declaration
protected:
    Node* head;
    Node* tail;
    int count;
public:
    DLinkedList() : head(NULL), tail(NULL), count(0) {};
    ~DLinkedList();
    void add(const T& e);
    void add(int index, const T& e);
    T removeAt(int index);
    bool removeItem(const T& item);
    bool empty();
    int size();
    void clear();
    T get(int index);
    void set(int index, const T& e);
    int indexOf(const T& item);
    bool contains(const T& item);
    void toString();
    Iterator begin()
    {
        return Iterator(this, true);
    }
    Iterator end()
    {
        return Iterator(this, false);
    }
public:
    class Node
    {
    private:
        T data;
        Node* next;
        Node* previous;
        friend class DLinkedList<T>;

        Iterator begin()
        {
            return Iterator(this, true);
        }
        Iterator end()
        {
            return Iterator(this, false);
        }

    public:
        Node()
        {
            this->previous = NULL;
            this->next = NULL;
        }

        Node(const T& data)
        {
            this->data = data;
            this->previous = NULL;
            this->next = NULL;
        }
    };
    class Iterator
    {
    private:
        DLinkedList<T>* pList;
        Node* current;
        int index; // is the index of current in pList
    public:
        Iterator(DLinkedList<T>* pList, bool begin);
        Iterator& operator=(const Iterator& iterator);
        void set(const T& e);
        T& operator*();
        bool operator!=(const Iterator& iterator);
        void remove();

        // Prefix ++ overload
        Iterator& operator++();

        // Postfix ++ overload
        Iterator operator++(int);
    };
};

/*
 * TODO: Implement class Iterator's method
 * Note: method remove is different from SLinkedList, which is the advantage of DLinkedList
 */
template <class T>
DLinkedList<T>::Iterator::Iterator(DLinkedList<T>* pList, bool begin)
{
    pList = pList;
    if (begin) {
        current = this->pList->head;
    }
    else {
        current = this->pList->tail;
    }
}

template <class T>
typename DLinkedList<T>::Iterator& DLinkedList<T>::Iterator::operator=(const DLinkedList<T>::Iterator& iterator)
{
    return &(DLinkedList<T>::Iterator(iterator->pList, (iterator->current == iterator->pList->head) ? 1 : 0);
}

template <class T>
void DLinkedList<T>::Iterator::set(const T& e)
{
    current->data = e;
}

template<class T>
T& DLinkedList<T>::Iterator::operator*()
{
    return &(current->data)
}

/*
 * TODO: Implement class Iterator's method
 * Note: method remove is different from SLinkedList, which is the advantage of DLinkedList
 */
template <class T>
DLinkedList<T>::Iterator::Iterator(DLinkedList<T>* pList, bool begin)
{
    this->pList = pList;
    if (begin) {
        this->current = pList->head;
        this->index = 0;
    }
    else {
        this->current = nullptr;
        this->index = pList->count;
    }
}

template <class T>
typename DLinkedList<T>::Iterator& DLinkedList<T>::Iterator::operator=(const DLinkedList<T>::Iterator& iterator)
{
    this->pList = iterator->pList;
    this->current = iterator->pList;
    this->index = iterator->index;
    return *this;
}

template <class T>
void DLinkedList<T>::Iterator::set(const T& e)
{
    if (current) {
        current->data = e;
    }
}

template<class T>
T& DLinkedList<T>::Iterator::operator*()
{
    return current->data;
}

template<class T>
void DLinkedList<T>::Iterator::remove()
{
    /*
    * TODO: delete Node in pList which Node* current point to.
    *       After that, Node* current point to the node before the node just deleted.
    *       If we remove first node of pList, Node* current point to nullptr.
    *       Then we use operator ++, Node* current will point to the head of pList.
    */
    Node* deleteNode = current;
    if (current == pList->head) {
        current = nullptr;
    }
    else {
        current = current->previous;
    }
    if (deleteNode) {
        pList->removeAt(index);
    }
    index--;
}

template<class T>
bool DLinkedList<T>::Iterator::operator!=(const DLinkedList::Iterator& iterator)
{
    return (this->current != iterator.current);
}

template<class T>
typename DLinkedList<T>::Iterator& DLinkedList<T>::Iterator::operator++()
{
    if (current) {
        current = current->next;
    }
    else {
        current = pList->head;
    }
    index++;
    return *this;
}

template<class T>
typename DLinkedList<T>::Iterator DLinkedList<T>::Iterator::operator++(int)
{
    DLinkedList<T>::Iterator ret(pList, 1);
    ret.current = this->current;
    if (current) {
        current = current->next;
    }
    else {
        current = pList->head;
    }
    index++;
    return ret;
}

template <class T>
void DLinkedList<T>::add(const T& e) {
    /* Insert an element into the end of the list. */
    Node* newNode = new Node(e);
    if (!tail) {
        tail = head = newNode;
    }
    else {
        tail->next = newNode;
        newNode->previous = tail;
        tail = tail->next;
    }
}

template<class T>
void DLinkedList<T>::add(int index, const T& e) {
    /* Insert an element into the list at given index. */
    if (!tail) {
        head = tail = new Node(e);
        return;
    }
    Node* inserter = head;
    for (int i = 0; i < index; i++) {
        inserter = inserter->next;
    }
    Node* newNode = new Node(e);
    newNode->next = inserter;
    newNode->previous = inserter->previous;
    if (inserter->previous) {
        inserter->previous->next = newNode;
    }
    else {
        head = newNode;
    }
    inserter->previous = newNode;
}

template<class T>
int DLinkedList<T>::size() {
    Node* counter = head;
    int cnt = 0;
    while (counter) {
        counter = counter->next;
        cnt++;
    }
    return cnt;
}

template<class T>
T DLinkedList<T>::get(int index) {
    /* Give the data of the element at given index in the list. */
    Node* scanner = head;
    for (int i = 0; i < index; i++) {
        scanner = scanner->next;
    }
    return scanner->data;
}

template <class T>
void DLinkedList<T>::set(int index, const T& e) {
    /* Assign new value for element at given index in the list */
    Node* scanner = head;
    for (int i = 0; i < index; i++) {
        scanner = scanner->next;
    }
    scanner->data = e;
}

template<class T>
bool DLinkedList<T>::empty() {
    /* Check if the list is empty or not. */
    return (head) ? false : true;
}

template<class T>
int DLinkedList<T>::indexOf(const T& item) {
    /* Return the first index wheter item appears in list, otherwise return -1 */
    Node* scanner = head;
    int index = 0;
    while (scanner)
    {
        if (scanner->data == item) {
            return index;
            break;
        }
        scanner = scanner->next;
        index++;
    }
    if (scanner) {
        return index;
    }
    return -1;
}

template<class T>
bool DLinkedList<T>::contains(const T& item) {
    /* Check if item appears in the list */
    return (indexOf(item) == -1) ? false : true;
}
