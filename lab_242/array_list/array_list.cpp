#include<iostream>
#include<vector>
#include<algorithm>

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

template<class T>
T ArrayList<T>::removeAt(int index){
    /*
    Remove element at index and return removed value 
    if index is invalid:
        throw std::out_of_range("index is out of range");
    */
    
    if (index < 0 || index >= count){
        throw std::out_of_range("index is out of range");
    }
    
    T removedElement = data[index];
    
    for (int i = index; i < count - 1; i++){
        data[i] = data[i+1];
    }
    
    count--;
    
    return removedElement;
}

template<class T>
bool ArrayList<T>::removeItem(T item)
{
    for (int i = 0; i < count; i++ ){
        if (item == data[i]){
            removeAt(i);
            return true;
        }
    } 
    return false;
}

template<class T>
void ArrayList<T>::clear()
{
    /* 
        Delete array if array is not NULL
        Create new array with: size = 0, capacity = 5
    */
    if (data != nullptr){
        delete[] data;
        data = nullptr;
    }
    
    data = new T[5];
    count = 0;
    capacity = 5;
    
}

bool consecutiveOnes(vector<int>& nums) 
{
    // STUDENT ANSWER
    int mode = 0;
    for (int num : nums) {
        if (mode == 0) {
            if (num == 1) {
                mode = 1;
            }
        }
        else if (mode == 1) {
            if (num != 1) {
                mode = 2;
            }
        }
        else {
            if (num == 1) {
                return false;
            }
        }
    }
    return true;
}

int buyCar(int* nums, int length, int k)
{
	int carCnt = 0;
	std::sort(nums, nums + length);
	for (int i = 0; i < length; i++) {
		if (k >= nums[i])
		{
			carCnt++;
			k -= nums[i];
		}
		else break;
	}
	return carCnt;
}

int equalSumIndex(vector<int>& nums) 
{
    // STUDENT ANSWER
    int sumL = 0;
    int sumR = 0;
    int currL = 0;
    int currR = nums.size() - 1;
    while (currL < currR) {
        if (sumL < sumR) {
            sumL += nums.at(currL++);
        }
        if (sumL > sumR) {
            sumR += nums.at(currR--);
        }
        if (sumL == sumR) {
            if (currL == currR) {
                return currL;
            }
            sumR += nums.at(currR--);
        }
    }
    if (sumL == sumR) {
        return currR;
    }
    return -1;
}

int longestSublist(vector<string>& words) 
{
    // STUDENT ANSWER
    if (words.size() == 0) return 0;
    int currentLength = 1; 
    int maxLength = 0; 
    
    for (int i = 1; i < words.size(); i++){
        if (words[i][0] == words[i-1][0]){
            currentLength++;
        } else {
            maxLength = max(maxLength, currentLength);
            currentLength = 1;
        }
    }
    maxLength = max(maxLength, currentLength);
    return maxLength; 
}