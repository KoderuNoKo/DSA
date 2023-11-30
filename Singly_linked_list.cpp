class LLNode {
public:
    int val;
    LLNode* next;
    LLNode() : val(0), next(nullptr) {}
    LLNode(int val, LLNode* next) : val(val), next(next) {}
};

LLNode* addLinkedList(LLNode* l0, LLNode* l1) {
    LLNode* result = nullptr;
    LLNode** node = &result;
    int carry = 0;
    while (l0 != nullptr || l1 != nullptr || carry > 0) {
        int sum = carry;
        if (l0 != nullptr) {
            sum += l0->val;
            l0 = l0->next;
        }
        if (l1 != nullptr) {
            sum += l1->val;
            l1 = l1->next;
        }
        carry = sum / 10;
        *node = new LLNode(sum % 10, nullptr);
        node = &((*node)->next);
    }
    return result;
}

