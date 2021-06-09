#pragma once
#include <queue>
#include <optional>
#include <string>
#include <cmath>
namespace tools {

namespace impl{
template<class T>
struct ListNodeGeneric {
    int val;
    ListNodeGeneric* next;
    explicit ListNodeGeneric(T x)
        : val(std::move(x))
        , next(nullptr)
    {
    }
    ListNodeGeneric(T x,ListNodeGeneric* next)
        : val(std::move(x))
        , next(next)
    {
    }
    auto operator <=>(const ListNodeGeneric&other) const=default;
};

template<class T>
class ConstLinkedListGenericIterator{

    using iterator_category = std::bidirectional_iterator_tag;
    using value_type      = T;
    using Node_t = ListNodeGeneric<value_type>;
    using Nodeptr        = Node_t*;
    using difference_type = ;
    using pointer         = typename _Mylist::pointer;
    using reference       = value_type&;

    Node_t* pointer;
};

template<class T>
class LinkedListGenericIterator:public ConstLinkedListGenericIterator<T>{
    using value_type = typename ConstLinkedListGenericIterator<T>::value_type;
    using Node_t = ListNodeGeneric<value_type>;
};



template<class T>
class LinkedListGeneric {
public:
    using value_type = T;
    using reference = const T&;
    using const_reference = const T&;
    using size_type = size_t;
    using Node_t = ListNodeGeneric<value_type>;
    using iterator = LinkedListGenericIterator;
public:


    LinkedListGeneric(const std::initializer_list<value_type>& list)
        :listSize(list.size())
    {
        if (list.size() == 0) {
            this->head = nullptr;
            return;
        }
        this->head = new Node_t(*list.begin());
        Node_t* curNode = this->head;
        for (auto&& element : list) {
            curNode->next = new Node_t(element);
            curNode = curNode->next;
        }
    }

    LinkedListGeneric(const LinkedListGeneric& other)
        : listSize(other.listSize)
        , head(nullptr)
    {
        if (other.head) {
            auto otherHead = other.head;
            this->head = new Node_t(otherHead->val);
            auto curHead = this->head;
            while (otherHead->next) {
                curHead->next = new Node_t(otherHead->next->val);
                curHead = curHead->next;
                otherHead = otherHead->next;
            }
        }
    }

    ~LinkedListGeneric()
    {
        while (head) {
            Node_t* delNode = head;
            head = head->next;
            delete delNode;
        }
    }
    LinkedListGeneric(LinkedListGeneric&& other)noexcept
        : listSize(other.listSize)
        , head(other.takeOwnedHead())
    {
        other.head=nullptr;
    }

    explicit LinkedListGeneric(Node_t* raw)
        :head(raw),
         listSize(countListSize(raw))
    {
    }



    void push_front(value_type val)
    {
        if (this->head) {
            auto curHead = this->head;
            while (curHead->next) {
                curHead = curHead->next;
            }
            curHead->next = new Node_t(std::move(val));
        }
        else {
            head = new Node_t(val);
        }
    }

    [[nodiscard]] size_type size() const
    {
        return this->listSize;
    }

    void push_back(value_type&& val)
    {
        if (head) {
            auto new_head = new Node_t(std::forward<T>(val));
            new_head->next = head;
            head = new_head;
        }
        else {
            head = new Node_t(std::forward<T>(val));
        }
    }


    [[nodiscard]]
    Node_t* takeOwnedHead()
    {
        Node_t* curHead = this->head;
        this->head = nullptr;
        return curHead;
    }

private:
    Node_t* head;
    size_type listSize{};

    static size_type countListSize(Node_t* head)
    {
        size_type counter = 0;
        while (head) {
            counter += 1;
            head = head->next;
        }
        return counter;
    }
};
}

using ListNode=impl::ListNodeGeneric<int>;
using LinkedList=impl::LinkedListGeneric<int>;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    explicit TreeNode(int x)
        : val(x)
        , left(nullptr)
        , right(nullptr)
    {
    }
};

class BinaryTree {
private:
    TreeNode* treeRootNode;

    void freeNode(TreeNode* root)
    {
        if (root == nullptr) {
            return;
        }
        freeNode(root->left);
        freeNode(root->right);
        delete root;
    };

    static std::vector<std::optional<int>> extractIntArray(std::string str)
    {
        std::vector<std::optional<int>> intList;
        str = str.substr(1, str.size() - 2);
        str += ',';
        for (int pos = 0; pos < str.size(); pos += 1) {
            int tailPos = static_cast<int>(str.find(',', pos));
            std::string intStr = str.substr(pos, tailPos - pos);

            if (intStr == "null") {
                intList.emplace_back(std::nullopt);
            }
            else if (intStr.empty()) {
                continue;
            }
            else {
                intList.emplace_back(stoi(intStr));
            }
            pos = tailPos;
        }
        return intList;
    }

    void setBinTreeByInt(std::vector<std::optional<int>>& list)
    {
        std::queue<TreeNode*> q;
        freeNode(this->treeRootNode);
        if (list.empty() || list[ 0 ] == std::nullopt) {
            return;
        }
        treeRootNode = new TreeNode(list[ 0 ].value());
        q.push(treeRootNode);
        for (int i = 1; i < list.size(); i++) {
            TreeNode* parent = q.front();
            if (list[ i ] != std::nullopt) {
                auto* newNode = new TreeNode(list[ i ].value());
                if ((i % 2) != 0) {
                    parent->left = newNode;
                }
                else {
                    parent->right = newNode;
                }
                q.push(newNode);
            }
            if (i % 2 == 0) {
                q.pop();
            }
        }
    };

    int treeHeight(TreeNode* root) const
    {
        if (root == nullptr) {
            return 0;
        }
        return std::max(treeHeight(root->left), treeHeight(root->right)) + 1;
    }

public:
    BinaryTree()
        : treeRootNode(nullptr){};

    explicit BinaryTree(const std::string& str)
        : treeRootNode(nullptr)
    {
        setBinTree(str);
    };
    ~BinaryTree()
    {
        freeNode(treeRootNode);
    };

    void setBinTree(const std::string& str)
    {
        std::vector intArray = extractIntArray(str);
        setBinTreeByInt(intArray);
    }

    TreeNode* getRoot()
    {
        return treeRootNode;
    }

    [[nodiscard, maybe_unused]] TreeNode* getInnerRoot()
    {
        return treeRootNode;
    }

    explicit operator TreeNode*()
    {
        return this->treeRootNode;
    }
    friend std::vector<std::optional<int>> flattenBinTree(const BinaryTree& tree);
};

[[nodiscard]] std::vector<std::optional<int>> flattenBinTree(const BinaryTree& tree)
{
    std::vector<std::optional<int>> flatIntList;
    std::queue<TreeNode*> q;
    q.push(tree.treeRootNode);

    if (tree.treeRootNode == nullptr) {
        return flatIntList;
    }

    while (!q.empty()) {
        TreeNode* ptn = q.front();
        if (ptn == nullptr) {
            flatIntList.emplace_back(std::nullopt);
        }
        else {
            flatIntList.emplace_back(ptn->val);
            q.push(ptn->left);
            q.push(ptn->right);
        }
        q.pop();
    }
    while (flatIntList.back() == std::nullopt) {
        flatIntList.pop_back();
    }
    return flatIntList;
}

static std::vector<std::string> convertStrList(std::vector<std::optional<int>>& flatIntList)
{
    std::vector<std::string> flatStrList;
    for (auto var : flatIntList) {
        if (var == std::nullopt) {
            flatStrList.emplace_back("null");
        }
        else {
            flatStrList.emplace_back(std::to_string(var.value()));
        }
    }
    return flatStrList;
}
}