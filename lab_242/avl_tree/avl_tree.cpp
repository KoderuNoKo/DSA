#include <iostream>
#include <math.h>
#include <queue>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"

enum BalanceValue
{
    LH = -1,
    EH = 0,
    RH = 1
};

void printNSpace(int n)
{
    for (int i = 0; i < n - 1; i++)
        cout << " ";
}

void printInteger(int &n)
{
    cout << n << " ";
}

template<class T>
class AVLTree
{
public:
    class Node;
private:
    Node *root;
protected:
    int getHeightRec(Node *node)
    {
        if (node == NULL)
            return 0;
        int lh = this->getHeightRec(node->pLeft);
        int rh = this->getHeightRec(node->pRight);
        return (lh > rh ? lh : rh) + 1;
    }
public:
    AVLTree() : root(nullptr) {}
    ~AVLTree(){}
    int getHeight()
    {
        return this->getHeightRec(this->root);
    }
    void printTreeStructure()
    {
        int height = this->getHeight();
        if (this->root == NULL)
        {
            cout << "NULL\n";
            return;
        }
        queue<Node *> q;
        q.push(root);
        Node *temp;
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
                cout << temp->data;
                q.push(temp->pLeft);
                q.push(temp->pRight);
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

    void insert(const T &value);

    int getBalance(Node*subroot){
        if(!subroot) return 0;
        return getHeightRec(subroot->pLeft)- getHeightRec(subroot->pRight);
    }

    Node* rotateRight(Node* root) {
        // TODO: Rotate and return new root after rotate
        if (!root) {
            return root;
        }
        if (!root->pLeft) {
            root->pRight->pLeft = root;
            return root->pRight;
        }
        // rotate
        Node* leftChild = root->pLeft;
        root->pLeft = leftChild->pRight;
        leftChild->pRight = root;
        return leftChild;
    }

    Node* rotateLeft(Node* root) {
        // TODO: Rotate and return new root after rotate
        if (!root) {
            return root;
        }
        if (!root->pRight) {
            root->pLeft->pRight = root;
            return root->pLeft;
        }
        // rotate
        Node* rightChild = root->pRight;
        root->pRight = rightChild->pLeft;
        rightChild->pLeft = root;
        return rightChild;
    }

    class Node
    {
    private:
        T data;
        Node *pLeft, *pRight;
        BalanceValue balance;
        friend class AVLTree<T>;

    public:
        Node(T value) : data(value), pLeft(NULL), pRight(NULL), balance(EH) {}
        ~Node() {}
    };

    Node* insertRec(const T &value, Node* root)
    {
        if (!root) {
            return new Node(value);
        }
        
        // BST insert
        if (value < root->data) {
            root->pLeft = this->insertRec(value, root->pLeft);
        }
        else {
            root->pRight = this->insertRec(value, root->pRight);
        }
        
        // balance resulted tree
        int balance = this->getHeightRec(root->pLeft) - this->getHeightRec(root->pRight);
        if (balance > RH && value < root->pLeft->data) {
            // left left
            return rotateRight(root);
        }
        if (balance < LH && value > root->pRight->data) {
            // right right
            return rotateLeft(root);
        }
        if (balance > RH && value > root->pLeft->data) {
            // left right
            root->pLeft = this->rotateLeft(root->pLeft);
            return rotateRight(root);
        }
        if (balance < LH && value < root->pRight->data) {
            // right left
            root->pRight = this->rotateRight(root->pRight);
            return rotateLeft(root);
        }
        return root;
    }

    void insert(const T &value){
        //TODO
        this->root = this->insertRec(value, this->root);
    }

    int getBalance(Node *root) {
        if (!root) {
            return 0;
        }
        return this->getHeightRec(root->pLeft) - this->getHeightRec(root->pRight);
    }

    Node* getInorderSuccessor(Node* root) {
        root = root->pLeft;
        if (!root) {
            return nullptr;
        }
        while (root->pRight) {
            root = root->pRight;
        }
        return root;
    }

    Node* removeRec(const T& value, Node* root)
    {
        if (!root) {
            return root;
        }
        
        // BST removal
        if (value < root->data) {
            root->pLeft = this->removeRec(value, root->pLeft);
        } 
        else if (value > root->data) {
            root->pRight = this->removeRec(value, root->pRight);
        }
        else {
            // found
            if (!root->pLeft && !root->pRight) {
                // leaf node
                delete root;
                return nullptr;
            }
            if (!root->pLeft || !root->pRight) {
                // missing one child
                Node* temp = (root->pLeft) ? root->pLeft : root->pRight;
                delete root;
                return temp;
            }
            // standard case
            Node* successor = this->getInorderSuccessor(root);
            if (!successor) {
                return root;
            }
            root->data = successor->data;
            root->pLeft = this->removeRec(root->data, root->pLeft);
        }
        
        // balance resulted tree
        root->balance = BalanceValue(this->getBalance(root));
        int lbalance = this->getBalance(root->pLeft);
        int rbalance = this->getBalance(root->pRight);
        if (root->balance > RH && lbalance >= 0) {
            // left left
            return rotateRight(root);
        }
        if (root->balance < LH && rbalance <= 0) {
            // right right
            return rotateLeft(root);
        }
        if (root->balance > RH && lbalance < 0) {
            // left right
            root->pLeft = this->rotateLeft(root->pLeft);
            return rotateRight(root);
        }
        if (root->balance < LH && rbalance > 0) {
            // right left
            root->pRight = this->rotateRight(root->pRight);
            return rotateLeft(root);
        }
        return root;
    }

    void remove(const T &value){
        //TODO
        this->root = this->removeRec(value, this->root);
    }

    void printInorderRec(Node* root) {
        if (!root) {
            return;
        }
        this->printInorderRec(root->pLeft);
        cout << root->data << " ";
        this->printInorderRec(root->pRight);
    }
    void printInorder(){
        //TODO
        this->printInorderRec(this->root);
    }

    bool searchRec(const T &value, Node* root) {
        if (!root) {
            return false;
        }
        if (value < root->data) {
            return this->searchRec(value, root->pLeft);
        }
        if (value > root->data) {
            return this->searchRec(value, root->pRight);
        }
        return true;
    }
    bool search(const T &value){
        //TODO
        return this->searchRec(value, this->root);
    }
};