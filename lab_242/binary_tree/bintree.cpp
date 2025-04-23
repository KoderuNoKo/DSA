#include<iostream>
#include<string>
#include<queue>
using namespace std;

template<class K, class V>
class BinaryTree
{
public:
    class Node;

private:
    Node *root;

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
        Node *pLeft, *pRight;
        friend class BinaryTree<K, V>;

    public:
        Node(K key, V value) : key(key), value(value), pLeft(NULL), pRight(NULL) {}
        ~Node() {}
    };

    void addNode(string posFromRoot, K key, V value)
    {
        if(posFromRoot == "")
        {
            this->root = new Node(key, value);
            return;
        }

        Node* walker = this->root;
        int l = posFromRoot.length();
        for (int i = 0; i < l-1; i++)
        {
            if (!walker)
                return;
            if (posFromRoot[i] == 'L')
                walker = walker->pLeft;
            if (posFromRoot[i] == 'R')
                walker = walker->pRight;
        }
        if(posFromRoot[l-1] == 'L')
            walker->pLeft = new Node(key, value);
        if(posFromRoot[l-1] == 'R')
            walker->pRight = new Node(key, value);
    }

    // STUDENT ANSWER BEGIN
    int count2ChildNode(Node* root) 
    {
        if (!root) {
            return 0;
        }
        int is2child = (root->pLeft && root->pRight) ? 1 : 0;
        return is2child + count2ChildNode(root->pLeft) + count2ChildNode(root->pRight);
    }
    
    int countTwoChildrenNode()
    {
        return count2ChildNode(this->root);
    }

    int getHeightHelp(Node* root)
    {
        if (!root) {
            return 0;
        }
        return 1 + max(getHeightHelp(root->pLeft), getHeightHelp(root->pRight));
    }

    int getHeight() {
        // TODO: return height of the binary tree.
        return getHeightHelp(this->root);
    }

    string traverseHelp(Node* root, int mode) 
    {
        if (!root) {
            return "";
        }
        stringstream ss;
        ss << root->value << " ";
        if (mode == 0) {
            return ss.str() + traverseHelp(root->pLeft, mode) + traverseHelp(root->pRight, mode);
        }
        if (mode == 1) {
            return traverseHelp(root->pLeft, mode) + ss.str() +  traverseHelp(root->pRight, mode);
        }
        return traverseHelp(root->pLeft, mode) +  traverseHelp(root->pRight, mode) + ss.str();
    }

    string preOrder() {
        // TODO: return the sequence of values of nodes in pre-order.
        return traverseHelp(this->root, 0);
    }

    string inOrder() {
        // TODO: return the sequence of values of nodes in in-order.
        return traverseHelp(this->root, 1);
    }

    string postOrder() {
        // TODO: return the sequence of values of nodes in post-order.
        return traverseHelp(this->root, 2);
    }

    void BFS()
    {
        queue<Node*> buffer;
        buffer.push(this->root);
        while(!buffer.empty()) {
            Node* curr = buffer.front();
            buffer.pop();
            if (curr->pLeft) {
                buffer.push(curr->pLeft);
            }
            if (curr->pRight) {
                buffer.push(curr->pRight);
            }
            cout << curr->value << " ";
        }
    }
    // STUDENT ANSWER END
};