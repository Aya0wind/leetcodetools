#include "utility.hpp"
#include <algorithm>
#include <numeric>
using std::vector;
using std::string;
using std::hash;
using std::array;
using std::accumulate;
using std::unordered_map;
using std::operator""s;
class Solution {
public:
    vector<vector<string>> groupAnagrams(const vector<string>& strs) {
        // 自定义对 array<int, 26> 类型的哈希函数
        auto arrayHash = [] (const array<int, 26>& arr) -> size_t {
            return accumulate(arr.begin(), arr.end(), 0u, [&](size_t acc, int num) {
                return (acc << 1) ^ hash<int>()(num);
            });
        };

        unordered_map<array<int, 26>, vector<string>, decltype(arrayHash)> mp(0, arrayHash);
        for (auto& str: strs) {
            array<int, 26> counts{};
            int length = str.length();
            for (int i = 0; i < length; ++i) {
                counts[str[i] - 'a'] ++;
            }
            mp[counts].emplace_back(str);
        }
        vector<vector<string>> ans;
        for (auto it = mp.begin(); it != mp.end(); ++it) {
            ans.emplace_back(it->second);
        }
        return ans;
    }
};


int main(){
    Solution a;
    tools::binTree b("[1,3,4,2,5,6,6]");
    auto list=tools::LinkedList({1,2,3,4,2,5});
    tools::print(list);
}
