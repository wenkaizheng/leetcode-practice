#include <iostream>
#include <queue>
using namespace std;
struct ListNode {
         int val;
         ListNode *next;
         ListNode() : val(0), next(nullptr) {}
         ListNode(int x) : val(x), next(nullptr) {}
         ListNode(int x, ListNode *next) : val(x), next(next) {}
};
ListNode* insert(ListNode* head, int val){
    if (head == nullptr){
        return new ListNode(val);
    }else{
        ListNode* copy = head;
        while(head->next){
            head = head->next;
        }
        head->next = new ListNode(val);
        return copy;
    }
}
void free_list(ListNode* head){
    if (head == nullptr){
        return;
    }else{
        ListNode* prev = nullptr;
        while(head){
            prev = head;
            head = head->next;
            delete prev;
        }
    }
}
void print_linked_list(ListNode* head){
    while(head){
        std::cout << head->val;
        head =  head->next;
    }
    std::cout << "\n";
}
class Solution {
public:
    struct compare
    {
        bool operator()(ListNode* &a,ListNode* &b)
        {
            return a->val>b->val;
        }
    };
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<ListNode*,vector<ListNode*>,compare>minh;
        for(int i=0;i<lists.size();i++)
        {
            if(lists[i]!=NULL) minh.push(lists[i]);
        }
        ListNode* head=new ListNode(0);
        ListNode* temp=head;
        while(minh.size()>0)
        {
            ListNode* p=minh.top();
            minh.pop();
            temp->next=new ListNode(p->val);
            temp=temp->next;
            if(p->next!=NULL) minh.push(p->next);
        }
        return head->next;
    }
};
class Solution1 {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode **pp = &head, *a, *b;
        while ((a = *pp) && (b = a->next)) {
            a->next = b->next;
            b->next = a;
            *pp = b;
            pp = &(a->next);

        }
        return head;
    }
};

class Solution2
{
public:

    ListNode* reverse(ListNode* first, ListNode* last)
    {
        ListNode* prev = last;

        while ( first != last )
        {
            auto tmp = first->next;
            first->next = prev;
            prev = first;
            first = tmp;
        }

        return prev;
    }

    ListNode* reverseKGroup(ListNode* head, int k)
    {
        auto node=head;
        for (int i=0; i < k; ++i)
        {
            if ( ! node  )
                return head; // nothing to do list too sort
            node = node->next;
        }

        auto new_head = reverse( head, node);
        head->next = reverseKGroup( node, k);
        return new_head;
    }
};

int main(){
    ListNode* head = insert(nullptr,1);
    head = insert(head,4);
    head = insert(head,5);
    ListNode* head1 = insert(nullptr,1);
    head1 = insert(head1,3);
    head1 = insert(head1,4);
    ListNode* head2 = insert(nullptr,2);
    head2 = insert(head2,6);
    Solution s = Solution();
    vector<ListNode*> test {head,head1,head2};
    ListNode* new_rv = s.mergeKLists(test);
    print_linked_list(new_rv);
    free_list(head);
    free_list(head1);
    free_list(head2);
    free_list(new_rv);

    ListNode* head3 = insert(nullptr,1);
    head3 = insert(head3,2);
    head3 = insert(head3,3);
    head3 = insert(head3,4);
    Solution1 s1 = Solution1();
    ListNode* rv = s1.swapPairs(head3);
    print_linked_list(rv);
    free_list(head3);

    ListNode* head4 = insert(nullptr,1);
    head4 = insert(head4,2);
    head4 = insert(head4,3);
    head4 = insert(head4,4);
    head4 = insert(head4,5);
    Solution2 s2 = Solution2();
    ListNode* rv2 = s2.reverseKGroup(head4,2);
    print_linked_list(rv2);
    free_list(head4);

    return 0;
}