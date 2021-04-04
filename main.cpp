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