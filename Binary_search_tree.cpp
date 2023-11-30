#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"
template<class T>
class BinarySearchTree
{
public:
    class Node;
private:
    Node* root;
public:
    BinarySearchTree() : root(nullptr) {}
    ~BinarySearchTree()
    {
        // You have to delete all Nodes in BinaryTree. However in this task, you can ignore it.
    }

    //Helping functions
    void addHelp(Node*& root, const T& value)
    {
        if (!root) {
            root = new Node(value);
            return;
        }
        if (value > root->value) {
            if (!root->pRight) {
                root->pRight = new Node(value);
                return;
            }
            return addHelp(root->pRight, value);
        }
        if (!root->pLeft) {
            root->pLeft = new Node(value);
            return;
        }
        return addHelp(root->pLeft, value);
    }
    void add(T value) {
        //TODO
        return addHelp(this->root, value);
    }

    Node* deleteNodeHelp(Node* root, const T& value)
    {
        // recursively call for subtree and return 
        // to parent of node to be deleted
        if (!root) {
            return root;
        }
        if (value > root->value) {
            root->pRight = deleteNodeHelp(root->pRight, value);
            return root;
        }
        if (value < root->value) {
            root->pLeft = deleteNodeHelp(root->pLeft, value);
            return root;
        }

        // code reach here -> Node to be deleted (delete node) found

        // delete node has missing child
        if (!root->pLeft) {
            Node* temp = root->pRight;
            delete root;
            return temp;
        }
        else if (!root->pRight) {
            Node* temp = root->pLeft;
            delete root;
            return temp;
        }

        //delete node has both child available 
        else
        {
            Node* replace = root->pRight; // node used to replace delete node (replace node)
            Node* replacePar = root; // parent of replace node



            while (replace->pLeft) { // replace node be the min (left most node)
                replacePar = replace;
                replace = replace->pLeft;
            }

            if (replacePar != root) { // replace node is not the child of delete node
                replacePar->pLeft = replace->pRight; // replace node is the left most node, 
                // i.e. replace->pLeft == nullptr,
                // but it may still have right child (1)
            }
            else {
                replacePar->pRight = replace->pRight; // same (1)
            }   

            // replace delete node with replace node
            root->value = replace->value;
            delete replace;

            // return current node to its parent to complete search process
            return root;
        }

    }
    void deleteNode(T value) {
        //TODO
        root = deleteNodeHelp(this->root, value);
    }

    string inOrderRec(Node* root) {
        stringstream ss;
        if (root != nullptr) {
            ss << inOrderRec(root->pLeft);
            ss << root->value << " ";
            ss << inOrderRec(root->pRight);
        }
        return ss.str();
    }

    string inOrder() {
        return inOrderRec(this->root);
    }

    class Node
    {
    private:
        T value;
        Node* pLeft, * pRight;
        friend class BinarySearchTree<T>;
    public:
        Node(T value) : value(value), pLeft(NULL), pRight(NULL) {}
        ~Node() {}
    };
};



class BSTNode 
{
public:
    int val;
    BSTNode* left;
    BSTNode* right;
    BSTNode() {
        this->left = this->right = nullptr;
    }
    BSTNode(int val) {
        this->val = val;
        this->left = this->right = nullptr;
    }
    BSTNode(int val, BSTNode*& left, BSTNode*& right) {
        this->val = val;
        this->left = left;
        this->right = right;
    }
};

vector<int> levelAlterTraverse(BSTNode* root) {
    // STUDENT ANSWER
    queue<BSTNode*> que;
    queue<BSTNode*> sta;
    vector<int> res;

    // init queue with the root node
    if (root) {
        que.push(root);
    }
    // tree level count
    int level = 1;
    while (!sta.empty() || !que.empty())
    {
        if (level % 2 == 1) // odd level - left to right traverse
        {
            while (!que.empty())
            {
                BSTNode* curr = que.front();
                que.pop();
                res.push_back(curr->val);
                if (curr->left) {
                    sta.push(curr->left);
                }
                if (curr->right) {
                    sta.push(curr->right);
                }
            }
        }
        else // even level - right to left traverse
        {
            stack<int> reRes; // reverse traverse
            while (!sta.empty())
            {
                BSTNode* curr = sta.front();
                sta.pop();
                reRes.push(curr->val);
                if (curr->left) {
                    que.push(curr->left);
                }
                if (curr->right) {
                    que.push(curr->right);
                }
            }
            while (!reRes.empty()) {
                res.push_back(reRes.top());
                reRes.pop();
            }
        }
        level++;
    }
    return res;
}

int kthSmallest(BSTNode* root, int k) {
    // STUDENT ANSWER
    vector<int> arr;
    queue<BSTNode*> trav;
    trav.push(root);
    while (!trav.empty())
    {
        BSTNode* curr = trav.front();
        arr.push_back(curr->val);
        trav.pop();
        if (curr->left) {
            trav.push(curr->left);
        }
        if (curr->right) {
            trav.push(curr->right);
        }
    }
    sort(arr.begin(), arr.end());
    return arr.at(k - 1);
}

class BTNode {
public:
    int val;
    BTNode* left;
    BTNode* right;
    BTNode() {
        this->left = this->right = NULL;
    }
    BTNode(int val) {
        this->val = val;
        this->left = this->right = NULL;
    }
    BTNode(int val, BTNode*& left, BTNode*& right) {
        this->val = val;
        this->left = left;
        this->right = right;
    }
};

void inTrav(BTNode* root, queue<int>& arr)
{
    if (!root) {
        return;
    }
    inTrav(root->left, arr);
    arr.push(root->val);
    inTrav(root->right, arr);
}

int rangeCount(BTNode* root, int lo, int hi)
{
    queue<int> arr;
    inTrav(root, arr);
    if (arr.empty()) {
        return 0;
    }
    while (arr.front() < lo) {
        arr.pop();
        if (arr.empty()) {
            return 0;
        }
    }
    int cnt = 0;
    while (arr.front() <= hi) {
        arr.pop();
        cnt++;
        if (arr.empty()) {
            return cnt;
        }
    }
    return cnt;
}

int singleChild(BSTNode* root) {
    // STUDENT ANSWER
    if (!root) {
        return 0;
    }
    if (!root->left && !root->right) {
        return 0;
    }
    if (!root->left) {
        return 1 + singleChild(root->right);
    }
    if (!root->right) {
        return 1 + singleChild(root->left);
    }
    return singleChild(root->left) + singleChild(root->right);
}

void addHelp(BSTNode*& root, const int& value)
{
    if (!root) {
        root = new BSTNode(value);
        return;
    }
    if (value > root->val) {
        if (!root->right) {
            root->right = new BSTNode(value);
            return;
        }
        return addHelp(root->right, value);
    }
    if (!root->left) {
        root->left = new BSTNode(value);
        return;
    }
    return addHelp(root->left, value);
}
void preTrav(BSTNode* root, BSTNode*& subroot, int lo, int hi)
{
    if (!root) {
        return;
    }
    if (root->val > hi) {
        return preTrav(root->left, subroot, lo, hi);
    }
    if (root->val < lo) {
        return preTrav(root->right, subroot, lo, hi);
    }
    addHelp(subroot, root->val);
    preTrav(root->left, subroot, lo, hi);
    preTrav(root->right, subroot, lo, hi);
}
BSTNode* subtreeWithRange(BSTNode* root, int lo, int hi)
{
    // STUDENT ANSWER
    BSTNode* walker = root;
    if (!walker) {
        return nullptr;
    }
    while (walker->val < lo) { // bring walker to the root of the subtree
        walker = walker->right;
    }

    BSTNode* subroot = nullptr; // init new tree to return
    preTrav(walker, subroot, lo, hi);
    return subroot;
}

template<class T>
class BinarySearchTree
{
public:
    class Node;

private:
    Node* root;

public:
    BinarySearchTree() : root(nullptr) {}
    ~BinarySearchTree()
    {
        // You have to delete all Nodes in BinaryTree. However in this task, you can ignore it.
    }

    class Node
    {
    private:
        T value;
        Node* pLeft, * pRight;
        friend class BinarySearchTree<T>;

    public:
        Node(T value) : value(value), pLeft(NULL), pRight(NULL) {}
        ~Node() {}
    };
    Node* addRec(Node* root, T value);
    void add(T value);
    // STUDENT ANSWER BEGIN
// You can define other functions here to help you.
// STUDENT ANSWER BEGIN
// You can define other functions here to help you.
    Node* findHelp(Node* root, const T& i)
    {
        if (!root) {
            return nullptr;
        }
        if (root->value == i) {
            return root;
        }
        if (root->value < i) {
            return findHelp(root->pRight, i);
        }
        return findHelp(root->pLeft, i);
    }
    bool find(T i) {
        // TODO: return true if value i is in the tree; otherwise, return false.
        if (findHelp(this->root, i)) {
            return true;
        }
        return false;
    }
    T sumHelp(Node* root, const T& l, const T& r)
    {
        if (!root) {
            return 0;
        }
        if (root->value > r) {
            return sumHelp(root->pLeft, l, r);
        }
        if (root->value < l) {
            return sumHelp(root->pRight, l, r);
        }
        return root->value + sumHelp(root->pLeft, l, r) + sumHelp(root->pRight, l, r);
    }
    T sum(T l, T r) {
        // TODO: return the sum of all element in the tree has value in range [l,r].
        return sumHelp(this->root, l, r);
    }

    // STUDENT ANSWER END

    T getMin() {
        //TODO: return the minimum values of nodes in the tree.
        if (!this->root) {
            return 0;
        }
        Node* walker = this->root;
        while (walker->pLeft) {
            walker = walker->pLeft;
        }
        return walker->value;
    }

    T getMax() {
        //TODO: return the maximum values of nodes in the tree.
        if (!this->root) {
            return 0;
        }
        Node* walker = this->root;
        while (walker->pRight) {
            walker = walker->pRight;
        }
        return walker->value;
    }
    // STUDENT ANSWER END
};