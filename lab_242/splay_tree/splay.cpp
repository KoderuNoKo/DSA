#include<iostream>
#include<string>

using namespace std;

class SplayTree {
    struct Node {
        int val;
        Node* pLeft;
        Node* pRight;
        Node* pParent;
        Node(int val = 0, Node* l = nullptr, Node* r = nullptr, Node* par = nullptr) : val(val), pLeft(l), pRight(r), pParent(par) { }
    };
    Node* root;

    // print the tree structure for local testing
    void printBinaryTree(string prefix, const Node* root, bool isLeft, bool hasRightSibling) {
        if (!root && isLeft && hasRightSibling) {
            cout << prefix << "├──\n";
        }
        if (!root) return;
        cout << prefix;
        if (isLeft && hasRightSibling) 
            cout << "├──";
        else 
            cout << "└──";
        cout << root->val << '\n';
        printBinaryTree(prefix + (isLeft && hasRightSibling ? "|  " : "   "), root->pLeft, true, root->pRight);
        printBinaryTree(prefix + (isLeft && hasRightSibling ? "|  " : "   "), root->pRight, false, root->pRight);
    }

    void printPreorder(Node* p) {
        if (!p) {
            return;
        }
        cout << p->val << ' ';
        printPreorder(p->pLeft);
        printPreorder(p->pRight);
    }

    //? rotate left: right child -> new subroot
    void rotateLeft(Node* subroot)
    {
        Node* right = subroot->pRight;
        if (!right) {
            return;
        }
        
        // update parent ptrs
        right->pParent = subroot->pParent;
        if (subroot->pParent) {
            if (subroot == subroot->pParent->pLeft) {
                subroot->pParent->pLeft = right;
            }
            else {
                subroot->pParent->pRight = right;
            }
        }
        else {
            // subroot is tree's root
            this->root = right;
        }
        
        // rotate
        subroot->pRight = right->pLeft;
        if (right->pLeft) {
            right->pLeft->pParent = subroot;
        }
        right->pLeft = subroot;
        subroot->pParent = right;
    }

    //? rotate right: left child -> new subroot
    void rotateRight(Node* subroot)
    {
        Node* left = subroot->pLeft;
        if (!left) {
            return;
        }
        
        // update parent ptrs
        left->pParent = subroot->pParent;
        if (subroot->pParent) {
            if (subroot == subroot->pParent->pLeft) {
                subroot->pParent->pLeft = left;
            }
            else {
                subroot->pParent->pRight = left;
            }
        }
        else {
            // subroot is tree's root
            this->root = left;
        }
        
        // rotate
        subroot->pLeft = left->pRight;
        if (left->pRight) {
            left->pRight->pParent = subroot;
        }
        left->pRight = subroot;
        subroot->pParent = left;
    }
public:
    SplayTree() {
        root = nullptr;
    }
    ~SplayTree() {
        // Ignore deleting all nodes in the tree
    }

    void printBinaryTree() {
        printBinaryTree("", root, false, false);
    }

    void printPreorder() {
        printPreorder(root);
        cout << "\n";
    }

    void splay(Node* p) {
        if (!p) {
            return;
        }
        
        while (p->pParent) {
            if (!p->pParent->pParent) {
                // parent is root -> single rotation
                if (p == p->pParent->pLeft) {
                    this->rotateRight(p->pParent);
                }
                else {
                    this->rotateLeft(p->pParent);
                }
            }
            else if (p == p->pParent->pLeft && p->pParent == p->pParent->pParent->pLeft) {
                // zig zig
                this->rotateRight(p->pParent->pParent);
                this->rotateRight(p->pParent);
            }
            else if (p == p->pParent->pRight && p->pParent == p->pParent->pParent->pRight) {
                // zag zag
                this->rotateLeft(p->pParent->pParent);
                this->rotateLeft(p->pParent);
            }
            else if (p == p->pParent->pRight && p->pParent == p->pParent->pParent->pLeft) {
                // zig zag
                this->rotateLeft(p->pParent);
                this->rotateRight(p->pParent);
            }
            else {
                // zag zag
                this->rotateRight(p->pParent);
                this->rotateLeft(p->pParent);
            }
        }
    }

    void insert(int val) {
        // BST insert
        if (!this->root) {
            this->root = new Node(val);
            return;
        }
        
        Node* walker = this->root;
        Node* parent = nullptr;
        
        while (walker) {
            parent = walker;
            if (val < walker->val) {
                walker = walker->pLeft;
            }
            else {
                walker = walker->pRight;
            }
        }
        
        // insert and splay
        if (val < parent->val) {
            parent->pLeft = new Node(val, nullptr, nullptr, parent);
            this->splay(parent->pLeft);
        }
        else {
            parent->pRight = new Node(val, nullptr, nullptr, parent);
            this->splay(parent->pRight);
        }
    }

    bool search(int val){
        //TODO
        Node* walker = this->root;
        Node* parent = nullptr;
        
        while (walker && walker->val != val) {
            parent = walker;
            if (val < walker->val) {
                walker = walker->pLeft;
            }
            else {
                walker = walker->pRight;
            }
        }
        
        if (!walker) {
            // not found
            this->splay(parent);
            return false;
        }
        else {
            // found
            this->splay(walker);
            return true;
        }
    }

    /*
    * 1. If root is NULL, return the root
    * 2. Search for the first node containing the given value val and splay it. 
    *    If val is present, the found node will become the root. 
    *    Else the last accessed leaf node becomes the root. 
    * 3. If new root's value is not equal to val, return NULL as val is not present.
    * 
    * 4. Else the value val is present, we remove root from the tree by the following steps:
    *   4.1 Split the tree into two tree: tree1 = root's left subtree and tree2 = root's right subtree
    *   4.2 If tree1 is NULL, tree2 is the new root
    *   4.3 Else, splay the leaf node with the largest value in tree1. tree1 will be a left skewed binary tree. 
    *       Make tree2 the right subtree of tree1. tree1 becomes the new root 
    *   4.4 Return the removed node.
    */
    Node* remove(int val){
        //TODO
        if (!this->root) {
            return this->root;
        }
        if (!this->search(val)) {
            // val is not present
            return nullptr;
        }

        // found, this->root now contain val
        Node* target = this->root;
        Node* tree1 = this->root->pLeft;
        Node* tree2 = this->root->pRight;

        // disconnect targer from the rest
        if (tree1) tree1->pParent = nullptr;
        if (tree2) tree2->pParent = nullptr;
        target->pLeft = target->pRight = target->pParent = nullptr;

        if (!tree1) {
            this->root = tree2;
        }
        else {
            // find + splay max node in tree1
            Node* maxNode = tree1;
            while (maxNode->pRight) {
                maxNode = maxNode->pRight;
            }
            this->splay(maxNode);

            // rebuild tree
            tree1 = maxNode;
            this->root = tree1;
            this->root->pRight = tree2;
            if (tree2){
                tree2->pParent = this->root;
            }
        }
        return target; 
    }
};