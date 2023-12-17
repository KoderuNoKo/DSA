#ifndef MAIN_H
#define MAIN_H
#include <bits/stdc++.h>
#include <string>

using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Utility
{
public:
	// check for legitimacy of guests' name
	static bool isLegit(string name)
	{
		if (name.length() < 3) {
			return false;
		}

		int cnt = 0;
		bool* checkList = new bool[52];
		for (int i = 0; i < 52; i++) {
			checkList[i] = false;
		}
		for (auto item : name)
		{
			if (isdigit(item)) {
				return false;
			}
			if (!checkList[Utility::charToIdx(item)]) {
				checkList[Utility::charToIdx(item)] = true;
				cnt++;
			}
		}

		return !(cnt < 3);
	}

	// translate a char into its equivalent index in the freq array
	static int charToIdx(char ch)
	{
		if (ch >= 'a' && ch <= 'z') {
			return ch - 'a';
		}
		if (ch >= 'A' && ch <= 'Z') {
			return 26 + ch - 'A';
		}
		return -1;
	}

	// translate freq array idx into its equivalent char
	static char idxToChar(int n)
	{
		if (n >= 0 && n < 26) {
			return n + 'a';
		}
		if (n >= 26 && n < 52) {
			return n + 39;
		}
		return '*';
	}

	// shift the character for caesar encoding
	static char charShift(char ch, int caesar)
	{
		int base = (ch < 'a' ? 'A' : 'a');
		return ((ch - base + caesar) % 26) + base;
	}

	// calculate ID from result and MAXSIZE
	static int hashID(const int& result, const int& MAXSIZE) { return result % MAXSIZE; }

	class Factorial
	{
		vector <long long> fact;

	public:
		Factorial()
		{
			fact.push_back(1);
			fact.push_back(1);
		}

		Factorial(size_t n)
		{
			fact.push_back(1);
			fact.push_back(1);
			for (size_t i = 2; i <= n; i++) {
				fact.push_back(i * fact[i - 1]);
			}
		}

		long long getFact(size_t n)
		{
			if (n < fact.size()) {
				return fact.at(n);
			}

			int lasti = fact.size() - 1;
			fact.resize(n + 1);
			for (size_t i = lasti; i <= n; i++)
			{
				fact.at(i) = i * fact.at(i - 1);
			}
			return fact.at(n);
		}

		long long nCr(size_t N, size_t R)
		{
			if (N < R) {
				return 0;
			}
			int res = getFact(N) / getFact(R);
			res /= fact[N - R];
			return res;
		}
	};
};

class HuffTree
{
public:
	class HuffNode
	{
		friend class HuffTree;
	public:
		char c;
		int freq;
		HuffNode* huffleft;
		HuffNode* huffright;

	public:
		HuffNode(char c, int freq) : c(c), freq(freq), huffleft(nullptr), huffright(nullptr)
		{}
		HuffNode(char c, int freq, HuffNode* left, HuffNode* right) : c(c), freq(freq), huffleft(left), huffright(right)
		{}
	};

	HuffTree(HuffNode* root) : huffroot(root)
	{}
	HuffTree(vector<int> charFreq)
	{
		huffroot = buildTree(charFreq);
	}
	HuffTree() : huffroot(nullptr)
	{}

	~HuffTree()
	{
		huffroot = clearTreeRec(huffroot);
	}

private:
	HuffNode* huffroot;
	map<char, string> table;

	/*
	void printNSpace(int n)
	{
		for (int i = 0; i < n - 1; i++) cout << " ";
	}
	void printTreeStructure(HuffNode* root)
	{
		int height = getHeightRec(root);
		if (root == NULL)
		{
			cout << "NULL\n";
			return;
		}
		queue<HuffNode*> q;
		HuffNode* temp = root;
		q.push(temp);
		int count = 0;
		int maxNode = 1;
		int level = 0;
		int space = pow(2, height);
		printNSpace(space / 2);
		while (!q.empty())
		{
			temp = q.front();
			q.pop();
			if (temp == NULL)
			{
				cout << " ";
				q.push(NULL);
				q.push(NULL);
			}
			else
			{
				if (temp->huffleft) cout << temp->freq;
				else if (temp->huffright) cout << temp->freq;
				else cout << temp->c;
				q.push(temp->huffleft);
				q.push(temp->huffright);
			}
			printNSpace(space);
			count++;
			if (count == maxNode)
			{
				cout << endl;
				count = 0;
				maxNode *= 2;
				level++;
				space /= 2;
				printNSpace(space / 2);
			}
			if (level == height)
				return;
		}
	}
	*/


	HuffNode* buildTree(const vector<int>& charFreq)
	{
		// initialize queue to build Huffman tree
		vector<HuffNode*> codingQueue;
		for (int i = 0; i < 52; i++)
		{
			if (charFreq[i] == 0) {
				continue;
			}

			int insFreq = charFreq[i];				// freq of the node to be inserted
			char insChar = Utility::idxToChar(i);	// char of the node to be inserted
			int insi = 0;							// position to insert new node in vector
			while (insi < (int)codingQueue.size())
			{
				if (insFreq < codingQueue.at(insi)->freq) {
					break;
				}
				insi++;
			}
			codingQueue.insert(codingQueue.begin() + insi, new HuffNode(insChar, charFreq[i]));
		}

		// start build tree
		while (codingQueue.size() > 1)
		{
			// remove 2 two element from the queue to form a new subtree
			HuffNode* left = codingQueue.at(0);
			HuffNode* right = codingQueue.at(1);
			codingQueue.erase(codingQueue.begin(), codingQueue.begin() + 2);

			// merge 2 trees into 1
			HuffNode* newHuffNode = new HuffNode('+', left->freq + right->freq, left, right);

			// maintain AVL properties
			int turns = 3;
			newHuffNode = makeBalance(newHuffNode, turns);

			int insi = 0;
			// find a suitable position to insert new subtree
			while (insi < (int)codingQueue.size())
			{
				if (newHuffNode->freq < codingQueue.at(insi)->freq) {
					break;
				}
				insi++;
			}

			// character got to root -> abort
			if (isalpha(newHuffNode->c)) {
				// clear current tree
				while (!codingQueue.empty()) {
					this->clearTreeRec(codingQueue.back());
					codingQueue.pop_back();
				}
				return nullptr;
			}

			codingQueue.insert(codingQueue.begin() + insi, newHuffNode);
		}

		// return root of tree
		return codingQueue.at(0);
	}

	void encryptRec(HuffNode* root, map<char, string>& table, string code)
	{
		if (!root) {
			return;
		}
		if (root->c != '+') {
			table[root->c] = code;
		}
		encryptRec(root->huffleft, table, code + "0");
		encryptRec(root->huffright, table, code + "1");
	}

	void encrypt()
	{
		table.clear();

		// one node tree
		if (!huffroot->huffleft && !huffroot->huffright) {
			table[huffroot->c] = "0";
			return;
		}

		// normal condition
		encryptRec(huffroot, table, "");
	}

	int getHeightRec(HuffNode* root)
	{
		if (!root) {
			return 0;
		}
		int lh = getHeightRec(root->huffleft);
		int rh = getHeightRec(root->huffright);
		return 1 + (lh > rh ? lh : rh);
	}

	int getBalance(HuffNode* root) { return getHeightRec(root->huffright) - getHeightRec(root->huffleft); }


	HuffNode* rotateRight(HuffNode* root)
	{
		HuffNode* temp = root->huffleft;
		HuffNode* rtemp = temp->huffright;
		temp->huffright = root;
		root->huffleft = rtemp;
		return temp;
	}

	HuffNode* rotateLeft(HuffNode* root)
	{
		HuffNode* temp = root->huffright;
		HuffNode* ltemp = temp->huffleft;
		temp->huffleft = root;
		root->huffright = ltemp;
		return temp;
	}

	HuffNode* makeBalance(HuffNode* root, int turns)
	{
		// leaf node reached, return 
		if (!root) {
			return nullptr;
		}

		//  examine root
		int balance = getBalance(root);
		for (int i = 0; i < turns && (balance < -1 || balance > 1); i++)
		{
			if (balance < -1) // left
			{
				if (getBalance(root->huffleft) > 0) {	// left right
					root->huffleft = rotateLeft(root->huffleft);
				}
				root = rotateRight(root);				// left left
			}
			else if (balance > 1) // right
			{
				if (getBalance(root->huffright) < 0) {	// right left
					root->huffright = rotateRight(root->huffright);
				}
				root = rotateLeft(root);				// right right
			}
			balance = getBalance(root);
			turns--;
		}
		root->huffleft = makeBalance(root->huffleft, turns);
		root->huffright = makeBalance(root->huffright, turns);
		return root;
	}

	void hand_printRec(HuffNode* root)
	{
		if (!root) {
			return;
		}

		// traverse to left child
		hand_printRec(root->huffleft);

		// print root
		if (isalpha(root->c)) {
			cout << root->c << "\n";
		}
		else {
			cout << root->freq << "\n";
		}

		// traverse to right child
		hand_printRec(root->huffright);
	}

public:
	HuffNode* clearTreeRec(HuffNode* root)
	{
		if (!root) {
			return nullptr;
		}
		root->huffleft = clearTreeRec(root->huffleft);
		root->huffright = clearTreeRec(root->huffright);
		delete root;
		return nullptr;
	}

	void newTree(const vector<int>& charFreq)
	{
		huffroot = clearTreeRec(huffroot);
		huffroot = buildTree(charFreq);
		encrypt();
	}

	int getResult(string name)
	{
		string codeStr = "";
		int i = name.length() - 1;

		while (codeStr.length() < 10 && i >= 0) {
			codeStr = table[name[i]] + codeStr;
			i--;
		}

		if (codeStr.length() > 10) {
			codeStr = codeStr.substr(codeStr.length() - 10, 10);
		}

		reverse(codeStr.begin(), codeStr.end());
		int result = 0;
		for (int i = codeStr.length() - 1; i >= 0; i--) {
			result += (codeStr[i] % 2) * pow(2, codeStr.length() - i - 1);
		}

		return result;
	}

	void hand_print()
	{
		hand_printRec(this->huffroot);
	}
};

class UnlimitedVoid
{
public:
	class TreeNode
	{
	public:
		int result;
		TreeNode* left;
		TreeNode* right;

		TreeNode(int result) : result(result), left(nullptr), right(nullptr)
		{}
		TreeNode(int result, TreeNode* left, TreeNode* right) : result(result), left(left), right(right)
		{}
		~TreeNode() = default;

		bool isLeaf() const { return (!left && !right); }
	};

	// A section in Gojo's restaurant, each TreeSection is a BST
	class TreeSection
	{
		TreeNode* root;
		queue<int> guestOrder;
		int size;
		Utility::Factorial* factCal;

		TreeNode* insertRec(TreeNode* root, const int& result)
		{
			if (!root) {
				return new TreeNode(result);
			}
			if (result < root->result) {
				root->left = insertRec(root->left, result);
				return root;
			}
			root->right = insertRec(root->right, result);
			return root;
		}

		TreeNode* clearSectionRec(TreeNode* root)
		{
			if (!root) {
				return nullptr;
			}
			root->left = clearSectionRec(root->left);
			root->right = clearSectionRec(root->right);
			delete root;
			return nullptr;
		}

		void limitless_print_Rec(TreeNode* root)
		{
			if (!root) {
				return;
			}
			limitless_print_Rec(root->left);
			cout << root->result << "\n";
			limitless_print_Rec(root->right);
		}

		void postOrderTravRec(TreeNode* root, vector<int>& postArr)
		{
			if (!root) {
				return;
			}

			postOrderTravRec(root->left, postArr);
			postOrderTravRec(root->right, postArr);
			postArr.push_back(root->result);
		}

		TreeNode* removeRec(TreeNode* root, int result)
		{
			if (!root) {	// Target not found or empty tree
				return root;
			}
			else if (result > root->result) {
				root->right = removeRec(root->right, result);
			}
			else if (result < root->result) {
				root->left = removeRec(root->left, result);
			}
			else			// Target found! now remove
			{
				if (!root->left && !root->right) {			// target is sad (has no child)
					delete root;
					return nullptr;
				}
				else if (!root->left) {						// target has one missing child, replace it with its remaining child		
					TreeNode* temp = root->right;
					delete root;
					return temp;
				}
				else if (!root->right) {
					TreeNode* temp = root->left;
					delete root;
					return temp;
				}
				else										// target is happy (has both child)
				{
					// find the node to replace the removed node
					TreeNode* replace = root->right;
					while (replace->left) {
						replace = replace->left;
					}

					root->result = replace->result;
					root->right = removeRec(root->right, replace->result);
				}
			}
			// return the current node to complete search process
			return root;
		}

	public:
		TreeSection() : root(nullptr), size(0)
		{
			factCal = new Utility::Factorial(5);
		}
		~TreeSection()
		{
			this->root = clearSectionRec(this->root);
			delete factCal;
		}

		void insert(const int& result)
		{
			this->root = insertRec(this->root, result);
			guestOrder.push(result);
			size++;
		}

		int getSize() const { return size; }

		void postOrderTrav(vector<int>& postArr)
		{
			postOrderTravRec(this->root, postArr);
		}

		void limitless_print() { limitless_print_Rec(this->root); }

		void remove(int quantity)
		{
			if (quantity >= size) {
				this->root = clearSectionRec(this->root);
				size = 0;
				return;
			}
			int target;
			for (int i = 0; i < quantity; i++) {
				target = guestOrder.front();
				guestOrder.pop();
				this->root = removeRec(this->root, target);
				size--;
			}
		}

		long long countPermut(vector<int> postOrder)
		{
			int N = postOrder.size();
			if (N <= 1) { // base case
				return 1;
			}

			// split the current array into two array contain left and right subtree
			int rootValue = postOrder[N - 1];
			vector<int> leftSub;
			vector<int> rightSub;

			for (int i = 0; i < N - 1; i++) {
				if (postOrder[i] < rootValue) {
					leftSub.push_back(postOrder[i]);
				}
				else if (postOrder[i] > rootValue) {
					rightSub.push_back(postOrder[i]);
				}
			}

			// recursively calculate the permutation on the left and right subtree
			long long left = countPermut(leftSub);
			long long right = countPermut(rightSub);

			// calculate the final result
			return left * right * factCal->nCr(leftSub.size() + rightSub.size(), leftSub.size());
		}
	};

private:
	TreeSection* sections;
	int maxsize;

public:
	UnlimitedVoid(int maxsize) : maxsize(maxsize)
	{
		sections = new TreeSection[maxsize];
	}

	~UnlimitedVoid()
	{
		if (sections) {
			delete[] sections;
		}
		sections = nullptr;
	}

	void insert(const int& result)
	{
		int id = Utility::hashID(result, maxsize);
		sections[id].insert(result);
	}

	void limitless_print(int num)
	{
		sections[num].limitless_print();
	}

	void kokusen_remove()
	{
		vector<int> postorder;
		for (int i = 0; i < maxsize; i++) {
			postorder.clear();
			sections[i].postOrderTrav(postorder);

			int quantity = sections[i].countPermut(postorder) % maxsize;

			sections[i].remove(quantity);
		}
	}
};

class MalevolentShrine
{
	class HeapSection
	{
		friend class MalevolentShrine;

		int label;
		int order;
		list<int>* guestList;

		void setHeapOrder(int i) { order = i; }

	public:
		HeapSection(int label) : label(label), order(0)
		{
			guestList = new list<int>;
		}
		HeapSection(int label, int order) : label(label), order(order)
		{}
		~HeapSection()
		{
			delete guestList;
		}

		void insert(int result)
		{
			guestList->push_back(result);
		}

		void removeNum(int num)
		{
			for (int i = 0; i < num && i < !guestList->empty(); i++) {
				cout << guestList->front() << "-" << this->getLabel() << "\n";
				guestList->pop_front();
			}
		}

		int getValue() const { return guestList->size(); }
		int getLabel() const { return label; }

		void print_cleave_base(int num)
		{
			list<int>::reverse_iterator it = guestList->rbegin();
			for (int i = 0; i < num && it != guestList->rend(); i++, it++)
			{
				cout << label << "-" << *it << "\n";
			}
		}

		int getHeapOrder() const { return order; }
	};

	struct compare_section
	{
		bool operator()(HeapSection* lhs, HeapSection* rhs)
		{
			if (lhs->getValue() == rhs->getValue()) {
				return lhs->getHeapOrder() > rhs->getHeapOrder();
			}
			return lhs->getValue() > rhs->getValue();
		}
	};

private:
	// heap vector field is used to store address of sections in the heap, (not the section itseft)
	vector<HeapSection*> heap;
	vector<HeapSection*> heapOrder;			// the order in which section num changes, used in KEITEIKEN

	// actual holder of sections
	vector<HeapSection*> sections;

	int maxsize;		// maxsize

	// store the information about heap order into the sections
	void saveOrder()
	{
		for (int i = 0; i < (int)heapOrder.size(); i++) {
			heapOrder[i]->setHeapOrder(i);
		}
	}

	// helper funtions used to update heapOrder
	void updateHeapOrder(int label)
	{
		for (int i = 0; i < (int)heapOrder.size(); i++)
		{
			// sections has already in the heap
			if (heapOrder[i]->getLabel() == label)
			{
				// bring it to the end of the heapOrder

				// remove it from its current pos
				HeapSection* temp = heapOrder[i];
				heapOrder.erase(heapOrder.begin() + i);

				// if it is not empty, put it back in the back
				if (temp->getValue() != 0) {
					heapOrder.push_back(temp);
				}

				saveOrder();
				return;
			}
		}

		// section is not in the heapOrder
		for (HeapSection* item : heap) {
			if (item->getLabel() == label) {
				heapOrder.push_back(item);
				break;
			}
		}

		saveOrder();
	}

	bool isLessThan(const HeapSection* lhs, const HeapSection* rhs)
	{
		if (lhs->getValue() == rhs->getValue()) {
			return lhs->getHeapOrder() < rhs->getHeapOrder();
		}
		return lhs->getValue() < rhs->getValue();
	}

	bool isGreaterThan(const HeapSection* lhs, const HeapSection* rhs)
	{
		if (lhs->getValue() == rhs->getValue()) {
			return lhs->getHeapOrder() > rhs->getHeapOrder();
		}
		return lhs->getValue() > rhs->getValue();
	}

	// heap operations
	void reheapDown(int idx)
	{
		if (idx * 2 + 1 >= (int)heap.size()) {
			return;
		}

		int childi = 2 * idx + 1;
		if (childi + 1 < (int)heap.size()) {
			childi += isLessThan(heap[childi + 1], heap[childi]);
		}

		if (isGreaterThan(heap[idx], heap[childi])) {
			swap(heap[idx], heap[childi]);
			reheapDown(childi);
		}
	}

	void reheapUp(int idx)
	{
		int parentIdx = (idx - 1) / 2;
		while (parentIdx > 0) {
			if (isGreaterThan(heap[parentIdx], heap[idx])) {
				swap(heap[parentIdx], heap[idx]);
			}
			idx = parentIdx;
			parentIdx = (parentIdx - 1) / 2;
		}
		if (isGreaterThan(heap[parentIdx], heap[idx])) {
			swap(heap[parentIdx], heap[idx]);
		}
	}

	int getRightChild(int idx) { return 2 * idx + 1; }
	int getLeftChild(int idx) { return 2 * idx + 2; }
	int getParent(int idx) { return (idx - 1) / 2; }

	void removeTop()
	{
		if (heap.size() <= 0) {
			return;
		}
		swap(heap[0], heap[heap.size() - 1]);
		heap.pop_back();
		reheapDown(0);
	}

	// remove element at idx from heap order
	void popHeap(int idx)
	{
		swap(heap[idx], heap[heap.size() - 1]);
		heap.pop_back();
		reheapDown(idx);
	}

	void print_cleave_rec(int root, int num)
	{
		if (root >= (int)heap.size()) {
			return;
		}
		heap[root]->print_cleave_base(num);
		print_cleave_rec(getLeftChild(root), num);
		print_cleave_rec(getRightChild(root), num);
	}

	// helper function to get sections for removing
	void getCandidate(vector<HeapSection*>& candidate, const int NUM)
	{
		// copy the heap of sections into a min heap
		priority_queue<HeapSection*, vector<HeapSection*>, compare_section> minHeap;
		for (auto item : heap) {
			minHeap.push(item);
		}

		for (int i = 0; i < NUM && !minHeap.empty(); i++) {
			candidate.push_back(minHeap.top());
			minHeap.pop();
		}
	}


public:
	MalevolentShrine(int maxsize) : maxsize(maxsize)
	{
		sections.resize(maxsize, nullptr);
		// initialize all sections at the beginning
		for (int i = 0; i < maxsize; i++) {
			sections[i] = new HeapSection(i + 1);
		}

		// at the beginning, no section present in the heap
		// heap.clear();
	}
	~MalevolentShrine()
	{
		for (int i = 0; i < maxsize; i++) {
			delete sections[i];
			sections[i] = nullptr;
		}
		heap.clear();
	}

	void insert(int result)
	{
		int id = Utility::hashID(result, maxsize);

		sections[id]->insert(result);

		if (sections[id]->getValue() == 1) // sections[id] is not yet in the heap, add it
		{
			heap.push_back(sections[id]);
			reheapUp(heap.size() - 1);

		}
		else // sections[id] has already in the heap, reheap it
		{
			int pos = 0;
			for (; pos < (int)heap.size(); pos++) {
				if (heap[pos]->getValue() == id)
				{
					reheapDown(pos);
					reheapUp(pos);
					break;
				}
			}
		}
		updateHeapOrder(sections[id]->getLabel());
	}


	void keiteiken_remove(int NUM)
	{
		// select NUM section 
		vector<HeapSection*> candidate;						// store the idx of sections to remove guest from
		getCandidate(candidate, NUM);

		// start remove guest
		int heapsize = heap.size();
		for (int i = 0; i < NUM && i < heapsize; i++)
		{
			for (int j = 0; j < (int)heap.size(); j++)
			{
				if (heap[j]->getLabel() == candidate.front()->getLabel()) {
					// remove NUM guest from the targeted section
					heap[j]->removeNum(NUM);

					// maintain heap
					if (heap[j]->getValue() == 0) {
						// section is now emmpty, remove it from the heap
						popHeap(j);
					}
					else {
						// section still has guest, reheap it
						reheapUp(j);
						reheapDown(j);
					}

					// remove current section out of candidate and start handling the next section
					candidate.erase(candidate.begin());

					// remove finished, update heap order
					updateHeapOrder(heap[j]->getLabel());
					break;
				}
			}
			
		}
	}

	void print_cleave(int num)
	{
		print_cleave_rec(0, num);
	}
};

class res
{
public:
	res(int maxsize)
	{
		hufftree = new HuffTree();
		gojoRes = new UnlimitedVoid(maxsize);
		sukunaRes = new MalevolentShrine(maxsize);
	}
	~res()
	{
		delete hufftree;
		delete gojoRes;
		delete sukunaRes;
	}

private:
	HuffTree* hufftree;
	UnlimitedVoid* gojoRes;
	MalevolentShrine* sukunaRes;

public:


	void LAPSE(string name)
	{
		if (!Utility::isLegit(name)) {
			return;
		}

		vector<int> charCnt(52, 0);
		for (char item : name) {
			charCnt[Utility::charToIdx(item)]++;
		}

		string caesarName = name;
		for (char& ch : caesarName) {
			ch = Utility::charShift(ch, charCnt[Utility::charToIdx(ch)]);
		}


		vector<int> caesarCharCnt(52, 0);
		for (char item : caesarName) {
			caesarCharCnt[Utility::charToIdx(item)]++;
		}

		hufftree->newTree(caesarCharCnt);
		int result = hufftree->getResult(caesarName);

		if (result % 2 == 1) {
			gojoRes->insert(result);
		}
		else {
			sukunaRes->insert(result);
		}
	}

	void KOKUSEN() { gojoRes->kokusen_remove(); }

	void KEITEIKEN(int NUM) { sukunaRes->keiteiken_remove(NUM); }

	void HAND() { hufftree->hand_print(); }

	void LIMITLESS(int num) { gojoRes->limitless_print(num - 1); }

	void CLEAVE(int num) { sukunaRes->print_cleave(num); }
};

void simulate(std::string filename)
{
	std::ifstream ss(filename);
	std::string str, name, num, maxsize;
	res* r = nullptr;
	while (ss >> str)
	{
		if (str == "MAXSIZE") {
			ss >> maxsize;
			int size = stoi(maxsize);
			//std::cout << "\n" << str << " " << size << std::endl;
			r = new res(size);
		}
		else if (str == "LAPSE") {
			ss >> name;
			//std::cout << "\n" << str << " " << name << std::endl;
			r->LAPSE(name);
		}
		else if (str == "KOKUSEN") {
			//std::cout << "\n" << str << std::endl;
			r->KOKUSEN();
		}
		else if (str == "KEITEIKEN") {
			ss >> num;
			//std::cout << "\n" << str << " " << num << endl;
			r->KEITEIKEN(stoi(num));
		}
		else if (str == "HAND") {
			//std::cout << "\n" << str << std::endl;
			r->HAND();
		}
		else if (str == "LIMITLESS") {
			ss >> num;
			//std::cout << "\n" << str << " " << num << std::endl;
			r->LIMITLESS(stoi(num));
		}
		else if (str == "CLEAVE") {
			ss >> num;
			//std::cout << "\n" << str << " " << num << std::endl;
			r->CLEAVE(stoi(num));
		}
	}
	delete r;
	return;
}

#endif
