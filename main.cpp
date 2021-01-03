#include <algorithm>
#include <numeric>
#include <unordered_map>

#include "utility.hpp"
using std::accumulate;
using std::array;
using std::hash;
using std::string;
using std::unordered_map;
using std::vector;

#include <iostream>
using namespace tools;
class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        ListNode* small=nullptr;
        ListNode* big= nullptr;
        ListNode* bighead= nullptr;
        ListNode* smallhead= nullptr;
        while(head){
           if(head->val<x){
               if (small){
                   small->next=head;
               }else{
                   smallhead=head;
               }
               small=head;
           }else{
               if (big){
                   big->next=head;
               }else{
                   bighead=head;
               }
               big=head;
           }
           head=head->next;
        }
        if(!big)
            return smallhead;
        if(!small)
            return bighead;
        small->next=bighead;
        big->next= nullptr;
        return smallhead;
    }
};
int main()
{
    using std::operator""s;
    using std::operator""sv;
    Solution a;
    LinkedList l{};
    LinkedList res(a.partition(l.getRoot(),1));
    print("123"sv);
}
