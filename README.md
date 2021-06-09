# LeetCode刷题工具
使用C++刷Leetcode总会遇到要把提供的测试用例复制进IDE测试代码的场景，Leetcode提供例如链表或者二叉树等数据要转换成C++对象比较麻烦。 </br>
本工具提供了一套使用Leetcode测试用例格式的字符串生成对应的数据结构的库函数，并提供了简单易用的格式化打印链表，二叉树，数组以及所有STL容器的库函数。
### 注:需要支持C++20及format库的编译器（最新的MSVC，并开启C++20支持）

+ 支持打印vector
```C++
#include "utility.hpp"
using namespace tools;
using std::vector;

#include <unordered_map>

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        std::unordered_map<int, int> hashtable;
        for (int i = 0; i < nums.size(); ++i) {
            auto it = hashtable.find(target - nums[i]);
            if (it != hashtable.end()) {
                return {it->second, i};
            }
            hashtable[nums[i]] = i;
        }
        return {};
    }
};

int main()
{
    Solution s;
    auto v=vector{1,2,3,4,5};
    tools::println("vector:{}",s.twoSum(v,5));
}

```

```C++
打印结果: [2,3]
```
+ 多维vector
```C++
#include "utility.hpp"
int main()
{
    auto v=vector{
        vector{1,2,3,4,5},
        vector{1,2,3,4,5},
        vector{1,2,3,4,5},
        vector{1,2,3,4,5}
    };
    tools::println("vector:{}",v);
}
```
```C++
vector:[[1,2,3,4,5],[1,2,3,4,5],[1,2,3,4,5],[1,2,3,4,5]]
```

+ 支持打印和从花括号列表构造链表

```C++
#include "utility.hpp"
int main()
{
    LinkedList list{1,2,3,4,5};
    tools::println("list:{}",list);
}
```
+ 支持打印和从字符串构造二叉树
```C++
#include "utility.hpp"
int main()
{
    BinaryTree tree("[1,2,3,4,5]");
    tools::println("tree:{}",tree);
}
```
+ 获取链表或二叉树的指针(注：在此以后原对象将无法使用，需要重新包装指针）
```C++
#include "utility.hpp"
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
    LinkedList list{1,2,3,4,5,6,7,8,9};
    ListNode* node = list.getOwnedHead();
    
    node=Solution{}.removeElements(node,6);
    
    //tools::println("list:{}",list); 错误!list内部的指针已经交由node管理
    
    tools::println("list:{}",LinkedList{node}); //正确，再次用LinkedList类包装指针
}
```
+ 打印映射容器和元组
```C++
#include "utility.hpp"
int main()
{
    auto hmap0=std::unordered_map<int,int>{};
    hmap0[1]=1;
    hmap0[2]=2;

    auto hmap1=std::unordered_map<int,std::string>{};
    hmap1[1]="123";
    hmap1[2]="123";

    auto tuple=std::make_tuple(1,1.23345,"abcde");

    auto pair=std::make_pair(1.23345,"abcde");


    tools::println("hashmap0:{}\nhashmap1:{}",hmap0,hmap1);

    tools::println("tuple:{}\npair:{}",tuple,pair);
}
```
结果
```C++
hashmap0:[(1 : 1),(2 : 2)]
hashmap1:[(1 : 1),(2 : 2)]
tuple:(1, 1.23345, abcde)
pair:(1.23345 : 1.23345)
```
#### 未完成
+ 对于存储浮点数的容器提供设定小数位数和对齐选项