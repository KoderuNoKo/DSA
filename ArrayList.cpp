#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

void removeEls(int* &nums, int length, const int idx)
{
	for (int i = idx; i < length - 1; i++) {
		nums[i] = nums[i + 1];
	}
	nums[length - 1];
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

bool consecutiveOnes(vector<int>& nums) {
	// STUDENT ANSWER
	bool foundOne = false;
	bool endOnes = false;
	for (int i = 0; i < nums.size(); i++)
	{
		if (nums.at(i) == 1) foundOne = true;

		if (nums.at(i) != 1 && foundOne) endOnes = true;
		
		if (nums.at(i) == 1 && foundOne && endOnes) return false;
	}
	return true;
}

int equalSumIndex(vector<int>& nums) {
	// STUDENT ANSWER
	int sumL = 0;
	int sumR = 0;
	int curL = 0;
	int curR = nums.size() - 1;
	while (curL < curR)
	{
		if (sumL < sumR)
		{
			sumL += nums.at(curL);
			curL++;
		}
		if (sumL > sumR)
		{
			sumR += nums.at(curR);
			curR--;
		}
		if (sumL == sumR)
		{
			if (curL == curR) return curL;
			sumR += nums.at(curR);
			curR--;
		}
	}
	if (sumL == sumR) return curR;
	else return -1;
}

int longestSublist(vector<string>& words) {
	// STUDENT ANSWER
	size_t letterCnt[26] = {0};
	for (const string& item : words) {
		letterCnt[
			(item[0] >= 'a') ? item[0] - 'a' : item[0] - 'A'
		]++;
	}

	int max = 0;
	for (const size_t& item : letterCnt) {
		cout << item << " ";
		if (max < item) max = item;
	}

	return max;
}

template <class T>
class ArrayList {
protected:
	T* data;        // dynamic array to store the list's items
	int capacity;   // size of the dynamic array
	int count;      // number of items stored in the array

public:
	ArrayList() { capacity = 5; count = 0; data = new T[5]; }
	~ArrayList() { delete[] data; }
	void    add(T e);
	void    add(int index, T e);
	int     size();
	bool    empty();
	void    clear();
	T       get(int index);
	void    set(int index, T e);
	int     indexOf(T item);
	bool    contains(T item);
	T       removeAt(int index);
	bool    removeItem(T item);
	void    ensureCapacity(int index);
};

template<class T>
void ArrayList<T>::ensureCapacity(int cap) {
	/*
		if cap == capacity:
			new_capacity = capacity * 1.5;
			create new array with new_capacity
		else: do nothing
	*/
	if (cap == capacity)
	{
		T* temp = new T[static_cast<int>(capacity * 1.5)];
		for (int i = 0; i < count; i++) {
			temp[i] = data[i];
		}
		delete[] data;
		data = temp;
		capacity *= 1.5;
	}
}

template <class T>
void ArrayList<T>::add(T e) {
	/* Insert an element into the end of the array. */
	ensureCapacity(this->count);
	data[count++] = e;
}

template<class T>
void ArrayList<T>::add(int index, T e) {
	/*
		Insert an element into the array at given index.
		if index is invalid:
			throw std::out_of_range("the input index is out of range!");
	*/
	if (index > count || index < 0) {
		throw std::out_of_range("the input index is out of range!");
	}
	ensureCapacity(this->count);
	for (int i = count; i > index; i--) {
		data[i] = data[i - 1];
	}
	data[index] = e;
	count++;
}

template<class T>
int ArrayList<T>::size() {
	/* Return the length (size) of the array */
	return count;
}

template<class T>
T ArrayList<T>::removeAt(int index) {
	/*
	Remove element at index and return removed value
	if index is invalid:
		throw std::out_of_range("index is out of range");
	*/
	if (index >= count || index < 0) {
		throw std::out_of_range("index is out of range");
	}

	T ret = data[index];
	
	for (int i = index; i < count - 1; i++) {
		data[i] = data[i + 1];
	}
	count--;
	return ret;
}

template<class T>
bool ArrayList<T>::removeItem(T item) {
	/* Remove the first apperance of item in array and return true, otherwise return false */
	for (int i = 0; i < count; i++) {
		if (item == data[i])
		{
			this->removeAt(i);
			return true;
		}
	}
	return false;
}

template<class T>
void ArrayList<T>::clear() {
	/*
		Delete array if array is not NULL
		Create new array with: size = 0, capacity = 5
	*/
	if (data) delete data;
	data = new T[5];
	this->capacity = 5;
	this->count = 0;
}

vector<int> updateArrayPerRange(vector<int>& nums, vector<vector<int>>& operations) {
	// STUDENT ANSWER
	for (vector<int>& item : operations)
	{
		for (int i = item.at(0); i <= item.at(1); i++) {
			nums.at(i) += item.at(2);
		}
	}
	return nums;
}