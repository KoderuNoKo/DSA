#include<iostream>
#include<vector>

using namespace std;

template <typename T> 
class IList {
public:
     virtual ~IList(){};
     virtual void       add(T e)=0;
     virtual void       add(int index, T e)=0;
     virtual T          removeAt(int index)=0;
     virtual bool       removeItem(T item, void (*removeItemData)(T)=0)=0;
     virtual bool       empty()=0;
     virtual int        size()=0;
     virtual void       clear()=0;
     virtual T&         get(int index)=0;
     virtual int        indexOf(T item)=0;
     virtual bool       contains(T item)=0;
     virtual string     toString(string (*item2str)(T&)=0 )=0;
};


template <class T>
class ArrayList {
protected:
    T* data;        // dynamic array to store the list's items
    int capacity;   // size of the dynamic array
    int count;      // number of items stored in the array
public:
    
ArrayList(){capacity = 5; count = 0; data = new T[5];}
    ~ArrayList(){ delete[] data; }    
    void    ensureCapacity(int cap);
    void    add(T e);
    void    add(int index, T e);
    int     size();
    bool    empty();
    void    clear();  //remove data and set the list to the initial condition
    T       get(int index);  //get the element at the index, if the index is out of range, "throw std::out_of_range("index is out of range");"
    void    set(int index, T e);  //set the index position in the list with the value e 
    int     indexOf(T item);  //get the first index of item in the list, else return -1
    bool    contains(T item);   //check if the item is in the list
    T       removeAt(int index);
    bool    removeItem(T item);
 
};


template<class T>
void ArrayList<T>::ensureCapacity(int cap) {
    /* 
        if cap > capacity: 
            new_capacity = capacity * 1.5;
            create new array with new_capacity
        else: do nothing
    */
    if (cap > capacity) {
        this->capacity = int(this->capacity * 1.5);
        T* newData = new T[this->capacity];
        for (int i = 0; i < this->count; i++) {
            newData[i] = this->data[i];
        }
        this->data = newData;
    }
    return;
}

template <class T>
void ArrayList<T>::add(T e) 
{
    /* Insert an element into the end of the array. */
    this->ensureCapacity(count + 1);
    this->data[count++] = e;
    return;
}

template<class T>
void ArrayList<T>::add(int index, T e) 
{
    /* 
        Insert an element into the array at given index.
        if index is invalid:
            throw std::out_of_range("the input index is out of range!");
    */
    this->ensureCapacity(count + 1);
    if (index > count) {
        throw std::out_of_range("The input index is out of range!");
    }
    for (int i = count; i > index; i--) {
        data[i] = data[i - 1];
    }
    data[index] = e;
    this->count++;
}

template<class T>
int ArrayList<T>::size() 
{
    /* Return the length (size) of the array */ 
    return this->count;
}

template<class T>
T ArrayList<T>::get(int index)
{
    if (index >= count || index < 0) {
        throw std::out_of_range("Index is out of range");
        return;
    }
    return this->data[index];
}

template<class T>
void ArrayList<T>::set(int index, T e) 
{
    if (index >= count || index < 0) {
        throw std::out_of_range("Index is out of range");
        return;
    }
    this->data[index] = e;
}

template<class T>
void ArrayList<T>::clear()
{
    this->count = 0;
}

template<class T>
bool ArrayList<T>::empty()
{
    return (this->count == 0);
}

template<class T>
int ArrayList<T>::indexOf(T item)
{
    for (int i = 0; i < count; i++) {
        if (data[i] == item) {
            return i;
        }
    }
    return -1;
}

template<class T>
bool ArrayList<T>::contains(T item)
{
    for (int i = 0; i < count; i++) {
        if (data[i] == item) {
            return true;
        }
    }
    return false;
}

vector<int> updateArrayPerRange(vector<int>& nums, vector<vector<int>>& operations) 
{
    // STUDENT ANSWER
    for (auto op : operations) {
        for (int i = op.at(0); i <= op.at(1); i++) {
            nums.at(i) += op.at(2);
        }
    }
}

vector<int> updateArrayPerRange(vector<int>& nums, vector<vector<int>>& operations) 
{
    // STUDENT ANSWER
    vector<int> incr(nums.size(), 0);
    for (vector<int> op : operations) {
        incr[op.at(0)] += op.at(2);
        incr[op.at(1) + 1] -= op.at(2); 
    }

    for (int i = 1; i < incr.size(); i++) {
        incr[i] += incr[i - 1];
    }

    for (int i = 0; i < nums.size(); i++) {
        nums[i] += incr[i];
    }
    
    return nums;
}



template <class T>
class SLinkedList {
public:
    class Node; // Forward declaration
protected:
    Node* head;
    Node* tail;
    int count;
public:
    SLinkedList();
    ~SLinkedList();
    void    add(const T& e);
    void    add(int index, const T& e);
    int     size();
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
        Node(T data, Node* next) {
            this->data = data;
            this->next = next;
        }
    };
};

template <class T>
void SLinkedList<T>::add(const T& e) {
    /* Insert an element into the end of the list. */
    if (count == 0) {
        this->head = this->tail = new Node(e);
        return;
    }
    this->tail->next = new Node(e);
    this->tail = this->tail->next;
    count++;
}

template<class T>
void SLinkedList<T>::add(int index, const T& e) {
    /* Insert an element into the list at given index. */
    if (index > count) {
        throw std::out_of_range("Index is out of range");
    }
    Node* newNode = new Node(e);
    if (index == count) {
        if (count == 0) {
            this->head = newNode;
        }
    }
}

template<class T>
int SLinkedList<T>::size() {
    /* Return the length (size) of list */ 
    return 0;
}
