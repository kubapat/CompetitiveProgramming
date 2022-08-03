/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* result  = new ListNode;
        int firstSum = l1->val + l2->val, toAdd = 0;
        if(firstSum>=10) {
            firstSum-=10;
            toAdd = 1;
        }
        
        result->val = firstSum;
        ListNode* head = result;
        while(true) {
            ListNode * nextOne = new ListNode;
            int val = 0;
            
            if(l1->next != NULL && l2->next != NULL) { 
                l1 = l1->next; 
                l2 = l2->next; 
                val = l1->val + l2->val + toAdd;
            } else if(l1->next != NULL && l2->next == NULL) { 
                l1 = l1->next; 
                val = l1->val + toAdd;
            } else if(l1->next == NULL && l2->next != NULL) { 
                l2 = l2->next; 
                val = l2->val + toAdd; 
            } else if(l1->next == NULL && l2->next == NULL && toAdd) val = toAdd;
              else break;
            
            
            if(val>=10) {
                val-=10;
                toAdd = 1;
            } else toAdd = 0;
            
            nextOne->val = val;
            result->next = nextOne;
            result       = result->next;
        }
        
        return head;
    }
};
