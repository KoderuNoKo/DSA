#include <iostream>
#include <utility>
#include <queue>
#include <stack>

using namespace std;

class BTNode {
    public: 
        int val; 
        BTNode *left; 
        BTNode *right; 
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

pair<int, int> longestPathSumHelp(BTNode* root)
{
    if (!root) {
        return pair<int, int>(0, 0);
    }
    pair<int, int> lc = longestPathSumHelp(root->left);
    pair<int, int> rc = longestPathSumHelp(root->right);

    if (lc.first > rc.first || (lc.first == rc.first && lc.second > rc.second)) {
        lc.first++; 
        lc.second += root->val;
        return lc;
    }
    else {
        rc.first++;
        rc.second += root->val;
        return rc;
    }
}

int longestPathSum(BTNode* root) 
{
    return longestPathSumHelp(root).second;
}

int sumDigitPath(BTNode* root) 
{
    if (!root) {
        return 0;
    }
    
    const int MOD = 27022001;
    int sum = 0;
    
    stack<pair<BTNode*, int>> buffer;
    buffer.push(make_pair(root, root->val % MOD));

    while (!buffer.empty()) {
        pair<BTNode*, int> curr = buffer.top();
        buffer.pop();  

        // dfs
        if (curr.first->left) {
            buffer.push(make_pair(curr.first->left, (curr.second*10 + curr.first->left->val)%MOD)); // value x10 when go deeper
        }
        if (curr.first->right) {
            buffer.push(make_pair(curr.first->right, (curr.second*10 + curr.first->right->val)%MOD));
        }

        // update sum at leaf
        if (!curr.first->left && !curr.first->right) {
            sum = (sum + curr.second) % MOD;
        }
    }

    return sum;
}

BTNode* lowestAncestorHelp(BTNode* root, int a, int b)
{
    if (!root) {
        return nullptr;
    }

    if (root->val == a || root->val == b) {
        // found a or b
        return root;
    }

    BTNode* lc = lowestAncestorHelp(root->left, a, b);
    BTNode* rc = lowestAncestorHelp(root->right, a, b);

    if (lc && rc) {
        // found lowest ancestor, return it up
        return root;
    }
    // return the node a or b or lowest ancestor upward
    return lc ? lc : rc;
}

int lowestAncestor(BTNode* root, int a, int b) {
    BTNode* res = lowestAncestorHelp(root, a, b);
    return res ? res->val : -1;
}