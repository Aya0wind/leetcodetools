#include <map>
#include <stack>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "utility.hpp"

using namespace tools;
using std::string;
using std::vector;
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        if(head){
            while (head&&head->val==val){
                auto next=head->next;
                delete head;
                head=next;
            }
            auto new_head=head;
            if(head){
                while(head->next){
                    auto next=head->next;
                    if(next->val==val){
                        head->next=next->next;
                        delete next;
                    }else{
                        head=head->next;
                    }
                }
            }
            return new_head;
        }
        return head;
    }
};
int main()
{
    tools::println("中文->{}","中文测试");

    auto v0=vector{1,2,3,4,5,6};

    auto v1=vector{
        vector{123,12,4,3},
        vector{123,12,4,3}
    };

    auto l0=LinkedList{1,2,3,4,5,6};

    auto b0=BinaryTree{"[1,2,3,4,5]"};

    auto s0=std::string("12345-std string");

    auto cc0="12345-cstring";

    auto hmap0=std::unordered_map<int,int>{};
    hmap0[1]=1;
    hmap0[2]=2;

    auto hmap1=std::unordered_map<int,std::string>{};
    hmap1[1]="123";
    hmap1[2]="123";

    auto map0=std::map<int,int>{};
    map0[1]=1;
    map0[2]=2;

    auto map1=std::map<int,std::string>{};
    map1[1]="123";
    map1[2]="123";


    auto tuple=std::make_tuple(1,1.23345,"abcde");

    auto pair=std::make_pair(1.23345,"abcde");

    tools::println(
        "vector1->{}\nvector2->{}\nLinkedList->{}\nBinaryTree->{}",
        v0,
        v1,
        l0,
        b0
        );

    tools::println(
        "std-string->{}\nc-string->{}",
        s0,
        cc0
    );

    tools::println("hashmap 0->{}\nhashmap 1->{}",
                   hmap0,
                   hmap1);

    tools::println("map 0->{}\nmap 1->{}",
                   map0,
                   map1);
    tools::println("tuple->{}\npair->{}\nfloat number->{:.4f}",
                   tuple,
                   pair,
                   1.23154687);

    LinkedList l1{1,2,6,3,4,5,6};

    tools::println("input->{}",l1);

    tools::println("output->{}",LinkedList{Solution{}.removeElements(l1. getOwnedHead(),6)});
}
