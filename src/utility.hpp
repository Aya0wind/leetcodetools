#pragma once
#include "leetcode_types.hpp"
#include "formatters.hpp"




inline std::locale chinese("zh_CN.UTF-8");

[[maybe_unused]] inline static struct LocalInitilizer{LocalInitilizer(){std::locale::global(chinese);}} initilizer;