#include <array>
#include <string_view>
#include <numeric>
#include "utility.hpp"
#include <algorithm>

int main(){
    auto vec=std::vector{1,2,3,4,5};
    std::next_permutation(vec.begin(),vec.end());
}