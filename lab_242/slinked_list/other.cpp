class LLNode {
    public:
        int val;
        LLNode* next;
        LLNode();   // Constructor: val = 0, next = nullptr
        LLNode(int val, LLNode* next);  // Constructor with customized data
};

LLNode* reverseLinkedList(LLNode* head)
{
    LLNode* prev = nullptr;
    LLNode* curr = head;
    LLNode* next = nullptr;

    while (prev) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    return prev;
}

// LLNode* addLinkedList(LLNode* l0, LLNode* l1, int carry = 0) 
// {
//     // STUDENT ANSWER
//     // end of both list
//     if (!l1 && !l0) {
//         if (carry) {
//             return new LLNode(1, nullptr);
//         }
//         else {
//             return nullptr;
//         }
//     }

//     int val0 = (l0) ? l0->val : 0;
//     int val1 = (l1) ? l1->val : 0;

//     // calculate carry
//     int sum = val0 + val1 + carry;
    
//     // call next digit
//     LLNode* next0 = (l0) ? l0->next : nullptr;
//     LLNode* next1 = (l1) ? l1->next : nullptr;
//     return new LLNode(
//         sum % 10,
//         addLinkedList(next0, next1, sum / 10)
//     );
// }

LLNode* addLinkedList(LLNode* l0, LLNode* l1) 
{
    LLNode Thread;
    LLNode * curr = & Thread;
    int carry = 0;
    
    while (l0 || l1 || carry)
    {
        int sum = carry;
        if (l0)
        {
            sum += l0->val;
            l0 = l0->next;
        }
        if (l1)
        {
            sum += l1->val;
            l1 = l1->next;
        }
        
        carry = sum / 10;
        curr->next = new LLNode(sum % 10, nullptr);
        curr = curr->next;
    }
    
    return Thread.next;
}

LLNode* rotateLinkedList(LLNode* head, int k) 
{
    // empty or single node
    if (!head || !head->next) {
        return head;
    }
    
    // reduce unnecessary rotation
    int length = 1;
    LLNode* tail = head;
    while (tail->next) {
        length++;
        tail = tail->next;
    }
    k = k % length;
    if (k == 0) {
        return head;
    }
    
    // find new tail
    LLNode* newTail = head;
    for (int i = 0; i < length - k - 1; i++) {
        newTail = newTail->next;
    }

    // rotate list
    LLNode* newHead = newTail->next;
    newTail->next = nullptr;
    tail->next = head;
    
    return newHead;
}