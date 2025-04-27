#include<iostream>
#include<vector>
#include<stack>
#include<queue>
#include<algorithm>

using namespace std;

class BSTNode {
public: 
    int val; 
    BSTNode *left; 
    BSTNode *right; 
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
    if (!root) {
        return {};
    }
    vector<int> result;
    queue<BSTNode*> buffer;
    buffer.push(root);
    bool l2r = false;

    while (!buffer.empty()) {
        int levelSize = buffer.size();
        vector<int> currLevel(levelSize);

        for (int i = 0; i < levelSize; i++) {
            BSTNode* currNode = buffer.front();
            buffer.pop();

            int index = l2r ? i : (levelSize - i);
            currLevel[index] = currNode->val;

            if (currNode->left) {
                buffer.push(currNode->left);
            }
            if (currNode->right) {
                buffer.push(currNode->right);
            }
        }

        // append one level at a time
        result.insert(result.end(), currLevel.begin(), currLevel.end());
        l2r = !l2r;
    }

    return result;
}

int countNode(BSTNode* root) {
    if (!root) {
        return 0;
    }
    return countNode(root->left) + countNode(root->right) + 1;
}
int kthSmallest(BSTNode* root, int k) {
    // STUDENT ANSWER
    if (!root) {
        return 0;
    }
    // count number of nodes smaller than current node
    int n = countNode(root->left);
    if (n + 1 < k) {
        // current num too small -> get greater
        // adjust k by the amount that the current node has already smaller
        return kthSmallest(root->right, k - n - 1);
    }
    if (n + 1 > k) {
        // current num to big -> get smaller
        return kthSmallest(root->left, k);
    }
    // found
    return root->val;
}

BSTNode* subtreeWithRange(BSTNode* root, int lo, int hi) {
    // STUDENT ANSWER
    if (!root) {
        return nullptr;
    }
    if (root->val < lo) {
        // left subtree out of lower bound
        return subtreeWithRange(root->right, lo, hi);
    }
    if (root->val > hi) {
        // right subtree out of higher bound
        return subtreeWithRange(root->left, lo, hi);
    }
    root->left = subtreeWithRange(root->left, lo, hi);
    root->right = subtreeWithRange(root->right, lo, hi);
    return root;
}