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

void printInteger(int& n)
{
    cout << n << " ";
}

template<class T>
class AVLTree
{
public:
    class Node;
private:
    Node* root;
protected:
    int getHeightRec(Node* node)
    {
        if (node == NULL)
            return 0;
        int lh = this->getHeightRec(node->pLeft);
        int rh = this->getHeightRec(node->pRight);
        return (lh > rh ? lh : rh) + 1;
    }
public:
    AVLTree() : root(nullptr) {}
    ~AVLTree() {}
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
        queue<Node*> q;
        q.push(root);
        Node* temp;
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

    //Helping functions
    Node* insertRec(Node* root, const T& value)
    {
        if (!root) {
            return new Node(value);
        }
        if (value >= root->data) {
            root->pRight = insertRec(root->pRight, value);
        }
        else {
            root->pLeft = insertRec(root->pLeft, value);
        }

            // balance
            int balance = getHeightRec(root->pRight) - getHeightRec(root->pLeft);

            // left left
            if (balance < -1 && value < root->pLeft->data) {
                return rotateRight(root);
            }

            // right right
            if (balance > 1 && value >= root->pRight->data) {
                return rotateLeft(root);
            }

            // left right
            if (balance < -1 && value >= root->pLeft->data) {
                root->pLeft = rotateLeft(root->pLeft);
                return rotateRight(root);
            }

            // right left
            if (balance > 1 && value < root->pRight->data) {
                root->pRight = rotateRight(root->pRight);
                return rotateLeft(root);
            }

            return root;
    }

    void insert(const T& value) {
        //TODO
        this->root = insertRec(this->root, value);   // insert value (unbalancy unhandled)
    }

    int getBalance(Node* subroot) {
        if (!subroot) return 0;
        return getHeightRec(subroot->pLeft) - getHeightRec(subroot->pRight);
    }
    Node* rotateRight(Node* root) {
        //TODO: Rotate and return new root after rotate
        Node* temp = root->pLeft;
        Node* rTemp = temp->pRight;
        temp->pRight = root;
        root->pLeft = rTemp;
        return temp;
    }

    Node* rotateLeft(Node* root) {
        //TODO: Rotate and return new root after rotate
        Node* temp = root->pRight;
        Node* lTemp = temp->pLeft;
        temp->pLeft = root;
        root->pRight = lTemp;
        return temp;
    }

    Node* deleteNodeHelp(Node* root, const T& value)
    {
        // recursively call for subtree and return 
        // to parent of node to be deleted
        if (!root) {
            return root;
        }
        if (value > root->data) {
            root->pRight = deleteNodeHelp(root->pRight, value);
            return root;
        }
        if (value < root->data) {
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
            root->data = replace->data;
            delete replace;

            // return current node to its parent to complete search process
            return root;
        }
        // balance
        int balance = getHeightRec(root->pRight) - getHeightRec(root->pLeft);

        // left left
        if (balance < -1 && value < root->pLeft->data) {
            return rotateRight(root);
        }

        // right right
        if (balance > 1 && value >= root->pRight->data) {
            return rotateLeft(root);
        }

        // left right
        if (balance < -1 && value >= root->pLeft->data) {
            root->pLeft = rotateLeft(root->pLeft);
            return rotateRight(root);
        }

        // right left
        if (balance > 1 && value < root->pRight->data) {
            root->pRight = rotateRight(root->pRight);
            return rotateLeft(root);
        }
    }

int balanced(Node* root)
{
    return getHeightRec(root->pRight) - getHeightRec(root->pLeft);
}

Node* rotate(Node* root)
{
    if (balanced(root) < -1) // left
    {
        if (balanced(root->pLeft) <= 0) { // left
            root = rotateRight(root);
        }
        else { // right
            root->pLeft = rotateLeft(root->pLeft);
            root = rotateRight(root);
        }
    }
    else if (balanced(root) > 1) // right
    {
        if (balanced(root->pRight) >= 0) { // right
            root = rotateLeft(root);
        }
        else { // left
            root->pRight = rotateRight(root->pRight);
            root = rotateLeft(root);
        }
    }
    return root;
}

Node* removeRec(Node* root, const T& value)
{
    if (!root) {        // empty tree
        return root;
    }
    
    if (value < root->data) {
        root->pLeft = removeRec(root->pLeft, value);
        root = rotate(root);
    }
    else if (value > root->data) {
        root->pRight = removeRec(root->pRight, value);
        root = rotate(root);
    }
    else // found
    {
        if (!root->pLeft && !root->pRight) {    // node is leaf
            delete root;
            return nullptr;
        }
        else if (!root->pLeft) {
            Node* temp = root->pRight;          // node dont has left child
            delete root;
            return temp;
        }
        else if (!root->pRight) {               // node dont has right child
            Node* temp = root->pLeft;
            delete root;
            return temp;
        }
        else                                    // node has both child
        {
            Node* replace = root->pLeft;
            while (replace->pRight) {
                replace = replace->pRight;
            }
            
            root->data = replace->data;
            root->pLeft = removeRec(root->pLeft, replace->data);
        }
    }
    return root;
}

void remove(const T& value)
{
    this->root = removeRec(this->root, value);
}


Node* removeRec(Node* root, const T& value)
{
    if (!root) {        // empty tree
        return root;
    }
    
    if (value < root->data) {
        root->pLeft = removeRec(root->pLeft, value);
        while (true)
        {
            if (balanced(root) ==1)
            {
                root->balance =LH;
                break;
            }
            if (balanced(root) ==0)
            {
                root->balance = EH;
                break;
            }
            if (balanced(root) ==-1)
            {
                root->balance = RH;
                break;
            }
            root = rotate(root);
        }
    }
    else if (value > root->data) {
        root->pRight = removeRec(root->pRight, value);
        while (true)
        {
            if (balanced(root) ==1)
            {
                root->balance =LH;
                break;
            }
            if (balanced(root) ==0)
            {
                root->balance = EH;
                break;
            }
            if (balanced(root) ==-1)
            {
                root->balance = RH;
                break;
            }
            root = rotate(root);
        }    
    }
    else // found
    {
        if (!root->pLeft && !root->pRight) {    // node is leaf
            delete root;
            return nullptr;
        }
        else if (!root->pLeft) {
            Node* temp = root->pRight;          // node dont has left child
            delete root;
            return temp;
        }
        else if (!root->pRight) {               // node dont has right child
            Node* temp = root->pLeft;
            delete root;
            return temp;
        }
        else                                    // node has both child
        {
            Node* replace = root->pLeft;
            while (replace->pRight) {
                replace = replace->pRight;
            }
            
            root->data = replace->data;
            root->pLeft = removeRec(root->pLeft, replace->data);
        }
    }
    return root;
}

void remove(const T& value)
{
    this->root = removeRec(this->root, value);
}

    void inTrav(Node* root)
    {
        if (!root) {
            return;
        }
        inTrav(root->pLeft);
        cout << root->data << " ";
        inTrav(root->pRight);
    }
    void printInorder() {
        //TODO
        inTrav(this->root);
    }

    bool searchRec(Node* root, const T& value)
    {
        if (!root) {
            return false;
        }
        if (value > root->data) {
            return searchRec(root->pRight, value);
        }
        if (value < root->data) {
            return searchRec(root->pLeft, value);
        }
        return true;
    }
    bool search(const T& value) {
        //TODO
        return searchRec(this->root, value);
    }

    class Node
    {
    private:
        T data;
        Node* pLeft, * pRight;
        BalanceValue balance;
        friend class AVLTree<T>;

    public:
        Node(T value) : data(value), pLeft(NULL), pRight(NULL), balance(EH) {}
        ~Node() {}
    };
};

