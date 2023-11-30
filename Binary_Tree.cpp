#include<iostream>
#include<string>
#include<queue>
#include<utility>
#include<stack>
using namespace std;

template<class K, class V>
class BinaryTree
{
public:
    class Node;

private:
    Node* root;

public:
    BinaryTree() : root(nullptr) {}
    ~BinaryTree()
    {
        // You have to delete all Nodes in BinaryTree. However in this task, you can ignore it.
    }

    class Node
    {
    private:
        K key;
        V value;
        Node* pLeft, * pRight;
        friend class BinaryTree<K, V>;

    public:
        Node(K key, V value) : key(key), value(value), pLeft(NULL), pRight(NULL) {}
        ~Node() {}
    };

    void addNode(string posFromRoot, K key, V value)
    {
        if (posFromRoot == "")
        {
            this->root = new Node(key, value);
            return;
        }

        Node* walker = this->root;
        int l = posFromRoot.length();
        for (int i = 0; i < l - 1; i++)
        {
            if (!walker)
                return;
            if (posFromRoot[i] == 'L')
                walker = walker->pLeft;
            if (posFromRoot[i] == 'R')
                walker = walker->pRight;
        }
        if (posFromRoot[l - 1] == 'L')
            walker->pLeft = new Node(key, value);
        if (posFromRoot[l - 1] == 'R')
            walker->pRight = new Node(key, value);
    }
    void BFS()
    {
        queue<Node*> nodesq;
        nodesq.push(this->root);
        while (!nodesq.empty())
        {
            Node* curr = nodesq.front();
            cout << curr->value << " ";

            nodesq.pop();

            if (curr->pLeft) {
                nodesq.push(curr->pLeft);
            }
            if (curr->pRight) {
                nodesq.push(curr->pRight);
            }
        }
    }
};

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

void DFS(BTNode* root, stack<pair<int, int>>& pathInfo, int length, int sum) // first: length; second: sum
{
    if (!root) {
        pathInfo.push(make_pair(length, sum));
        return;
    }
    DFS(root->left, pathInfo, length + 1, sum + root->val);
    DFS(root->right, pathInfo, length + 1, sum + root->val);
}

int longestPathSum(BTNode* root)
{
    stack<pair<int, int>> pathInfo;
    DFS(root, pathInfo, 0, 0);
    int sum = 0, length = 0;
    while (!pathInfo.empty())
    {
        if (pathInfo.top().first > length) {
            length = pathInfo.top().first;
            sum = pathInfo.top().second;
        }
        else if (pathInfo.top().first == length) {
            if (pathInfo.top().second > sum) {
                sum = pathInfo.top().second;
            }
        }
        pathInfo.pop();
    }
    return sum;
}

bool findPath(BTNode* root, stack<int>& path, int k)
{
    if (!root) {
        return false;
    }

    path.push(root->val);

    if (root->val == k) {
        return true;
    }
    if ((root->left && findPath(root->left, path, k)) || (root->right && findPath(root->right, path, k))) {
        return true;
    }

    path.pop();
    return false;
}

int lowestAncestor(BTNode* root, int a, int b)
{
    stack<int> pathA, pathB;
    findPath(root, pathA, a);
    findPath(root, pathB, b);

    stack<int> pathAr, pathBr;

    while (!pathA.empty()) {
        pathAr.push(pathA.top());
        pathA.pop();
    }

    while (!pathB.empty()) {
        pathBr.push(pathB.top());
        pathB.pop();
    }

    int temp = 0;
    while (!(pathAr.empty() || pathBr.empty())) {
        if (pathAr.top() != pathBr.top()) {
            break;
        }
        temp = pathAr.top();
        pathAr.pop();
        pathBr.pop();
    }
    return temp;
}

long long sumDigitPathHelp(BTNode* root, long long res) {
    if (!root) {
        return 0;
    }

    res = (10 * res + root->val) % 27022001;

    if (!root->left && !root->right) {
        return res;
    }

    return sumDigitPathHelp(root->left, res) + sumDigitPathHelp(root->right, res);
}

int sumDigitPath(BTNode* root)
{
    if (!root) {
        return 0;
    }
    return (sumDigitPathHelp(root, 0) % 27022001);
}

template<class K, class V>
class BinaryTree
{
public:
    class Node;

private:
    Node* root;

public:
    BinaryTree() : root(nullptr) {}
    ~BinaryTree()
    {
        // You have to delete all Nodes in BinaryTree. However in this task, you can ignore it.
    }

    class Node
    {
    private:
        K key;
        V value;
        Node* pLeft, * pRight;
        friend class BinaryTree<K, V>;

    public:
        Node(K key, V value) : key(key), value(value), pLeft(NULL), pRight(NULL) {}
        ~Node() {}
    };

    void addNode(string posFromRoot, K key, V value)
    {
        if (posFromRoot == "")
        {
            this->root = new Node(key, value);
            return;
        }

        Node* walker = this->root;
        int l = posFromRoot.length();
        for (int i = 0; i < l - 1; i++)
        {
            if (!walker)
                return;
            if (posFromRoot[i] == 'L')
                walker = walker->pLeft;
            if (posFromRoot[i] == 'R')
                walker = walker->pRight;
        }
        if (posFromRoot[l - 1] == 'L')
            walker->pLeft = new Node(key, value);
        if (posFromRoot[l - 1] == 'R')
            walker->pRight = new Node(key, value);
    }

    // STUDENT ANSWER BEGIN
    // You can define other functions here to help you.

    int countHelp(Node* root)
    {
        if (root->pLeft && root->pRight) {
            return 1 + countHelp(root->pLeft) + countHelp(root->pRight);
        }
        return 0;
    }
    int countTwoChildrenNode()
    {
        return countHelp(this->root);
    }

    int getHeightHelp(Node* root)
    {
        if (!root) {
            return 0;
        }
        int hLeft = getHeightHelp(root->pLeft);
        int hRight = getHeightHelp(root->pRight);
        return 1 + ((hLeft > hRight) ? hLeft : hRight);
    }
    int getHeight() {
        // TODO: return height of the binary tree.
        return getHeightHelp(this->root);
    }

    string preTrav(Node* root)
    {
        if (!root) {
            return "";
        }
        return to_string(root->value) + " " + preTrav(root->pLeft) + preTrav(root->pRight);
    }
    string preOrder() {
        // TODO: return the sequence of values of nodes in pre-order.
        return preTrav(this->root);
    }

    string inTrav(Node* root)
    {
        if (!root) {
            return "";
        }
        return inTrav(root->pLeft) + to_string(root->value) + " " + inTrav(root->pRight);
    }
    string inOrder() {
        // TODO: return the sequence of values of nodes in in-order.
        return inTrav(this->root);
    }

    string postTrav(Node* root)
    {
        if (!root) {
            return "";
        }
        return postTrav(root->pLeft) + postTrav(root->pRight) + to_string(root->value) + " ";
    }
    string postOrder() {
        // TODO: return the sequence of values of nodes in post-order.
        return postTrav(this->root);
    }
    //Helping functions
    int sumLeafRec(Node* root)
    {
        if (!root) {
            return 0;
        }
        if (!root->pLeft && !root->pRight) {
            return root->value;
        }
        return sumLeafRec(root->pLeft) + sumLeafRec(root->pRight);
    }
    int sumOfLeafs() {
        //TODO
        return sumLeafRec(this->root);
    }


    // STUDENT ANSWER END
};