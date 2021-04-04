#LeetCode刷题工具
使用C++刷Leetcode总会遇到要把提供的测试用例复制进IDE测试代码的场景，Leetcode提供例如链表或者二叉树等数据要转换成C++对象比较麻烦。 </br>
本工具提供了一套使用Leetcode测试用例格式的字符串生成对应的数据结构的库函数，并提供了简单易用的直接打印链表，二叉树，数组等容器的库函数。
### 注:需要支持C++20的编译器（gcc 10及以上，或MSVC 14.23及以上，并开启C++20支持）

+ 支持打印vector（多维也可）
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
    print(s.twoSum(v,7));
}

```

```C++
打印结果: [2,3]
```
多维vector
```C++
int main()
{
    Solution s;
    auto v=vector{
        vector{1,2,3,4,5},
        vector{1,2,3,4,5},
        vector{1,2,3,4,5},
        vector{1,2,3,4,5}
    };
    print(v);
}
```
```C++
[
    [1,2,3,4,5],
    [1,2,3,4,5],
    [1,2,3,4,5],
    [1,2,3,4,5],
]
```

+ 支持打印和从数组构造链表

```C++
int main()
{
    LinkedList list({1,2,3,4,5});
    print(list);
}
```
+ 支持打印和从字符串构造二叉树
```C++
int main()
{
    BinaryTree tree("[1,2,3,4,5]");
    print(tree);
}
```
