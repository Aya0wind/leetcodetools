#include <string_view>
#include <numeric>
#include "utility.hpp"
#include <algorithm>

using namespace tools;
class Solution {
public:
    static TreeNode* buildTreeImpl(const int* first,const int* last,vector<int>& rootSequnce,int& lastRoot){
        if(first==last){
            return nullptr;
        }
        if(last-first==1){
            --lastRoot;
            return new TreeNode(*first);
        }
        int end= rootSequnce[lastRoot];
        auto divide=std::find(first,last,end);
        auto root=new TreeNode(*divide);
        --lastRoot;
        root->right=buildTreeImpl(divide+1,last,rootSequnce,lastRoot);
        root->left=buildTreeImpl(first,divide,rootSequnce,lastRoot);
        return root;
    }

    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        if(inorder.empty()){
            return nullptr;
        }
        int lastRoot=postorder.size()-1;
        return buildTreeImpl(inorder.data(),inorder.data()+inorder.size(),postorder,lastRoot);
    }
};

int main(){
   Solution a;
   auto vec1=vector{9,3,15,20,7};
   auto vec2=vector{9,15,7,20,3};
   print(a.buildTree(vec1,vec2));
}