//
// Created by 12003 on 2020/8/12.
//

#ifndef LEETCODECPP_UTILITY_HPP
#define LEETCODECPP_UTILITY_HPP
#include <concepts>
#include <iostream>
#include <queue>
#include <ranges>
#include <sstream>
#include <string>
#include <vector>

namespace tools {

using namespace std;
struct ListNode {
    int val;
    ListNode* next;
    explicit ListNode(int x)
        : val(x)
        , next(nullptr)
    {
    }
};

[[maybe_unused]] ListNode* createListNode(const std::initializer_list<int>& list)
{
    vector num(list);
    if (num.empty())
        return nullptr;
    else {
        auto* head = new ListNode(num[ 0 ]);
        ListNode* curNode = head;
        for (int i = 1; i < num.size(); i++) {
            curNode->next = new ListNode(num[ i ]);
            curNode = curNode->next;
        }
        return head;
    }
}

void printLinkedList(ListNode* head)
{
    ListNode* curNode = head;
    while (curNode != nullptr) {
        cout << curNode->val << " -> ";
        curNode = curNode->next;
    }
    cout << "nullptr" << endl;
}

[[maybe_unused]] void deleteLinkedList(ListNode* head)
{
    ListNode* curNode = head;
    while (curNode != nullptr) {
        ListNode* delNode = curNode;
        curNode = curNode->next;
        delete delNode;
    }
}
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

class binTree {
private:
    TreeNode* m_root;
    inline static constexpr auto NULLPTR_VAR = std::numeric_limits<int>::max();
    void freeNode(TreeNode* root)
    {
        if (!root)
            return;
        freeNode(root->left);
        freeNode(root->right);
        delete root;
    };

    static vector<int> extractIntArray(string str)
    {
        vector<int> intList;
        str = str.substr(1, str.size() - 2);
        str += ',';
        for (int pos = 0; pos < str.size(); pos += 1) {
            int tailPos = str.find(',', pos);
            string intStr = str.substr(pos, tailPos - pos);

            if (intStr == "null")
                intList.push_back(NULLPTR_VAR);
            else if (intStr.empty())
                continue;
            else
                intList.push_back(stoi(intStr));
            pos = tailPos;
        }
        return intList;
    }

    void setBinTreeByInt(vector<int>& list)
    {
        queue<TreeNode*> q;
        freeBinTree();

        if (list.empty() || list[ 0 ] == NULLPTR_VAR)  // "[]" equal "[null]"
            return;

        // set m_root
        m_root = new TreeNode(list[ 0 ]);
        q.push(m_root);
        for (int i = 1; i < list.size(); i++) {
            TreeNode* parent = q.front();
            if (list[ i ] != NULLPTR_VAR) {
                auto* newNode = new TreeNode(list[ i ]);
                if (i % 2) {
                    parent->left = newNode;
                }
                else {
                    parent->right = newNode;
                }
                q.push(newNode);
            }
            if (i % 2 == 0)
                q.pop();
        }
    };

    [[nodiscard]] vector<int> flattenBinTree() const
    {
        vector<int> flatIntList;
        queue<TreeNode*> q;
        q.push(m_root);

        if (!m_root)
            return flatIntList;

        while (!q.empty()) {
            TreeNode* ptn = q.front();
            if (!ptn) {
                flatIntList.push_back(NULLPTR_VAR);
            }
            else {
                flatIntList.push_back(ptn->val);
                q.push(ptn->left);
                q.push(ptn->right);
            }
            q.pop();
        }
        while (flatIntList.back() == NULLPTR_VAR) {
            flatIntList.pop_back();
        }
        return flatIntList;
    }

    static vector<string> convertStrList(vector<int>& flatIntList)
    {
        vector<string> flatStrList;
        for (auto var : flatIntList) {
            if (var == NULLPTR_VAR)
                flatStrList.emplace_back("null");
            else
                flatStrList.push_back(to_string(var));
        }
        return flatStrList;
    }

    int treeHeight(TreeNode* root) const
    {
        if (root == nullptr)
            return 0;
        return max(treeHeight(root->left), treeHeight(root->right)) + 1;
    }

    void writeRootToBoard(TreeNode* root, int height, int left, int right, vector<vector<string>>& board) const
    {
        if (root == nullptr)
            return;
        int mid = (left + right) / 2;
        board[ height ][ mid ] = to_string(root->val);
        writeRootToBoard(root->left, height + 1, left, mid - 1, board);
        writeRootToBoard(root->right, height + 1, mid + 1, right, board);
    }

    vector<vector<string>> writeTreeToBoard(TreeNode* root, vector<vector<string>>& board) const
    {
        int height = treeHeight(root);
        board = vector<vector<string>>(height, vector<string>(pow(2, height) - 1, ""));
        writeRootToBoard(root, 0, 0, static_cast<int>(pow(2, height) - 2), board);
        return board;
    }

public:
    binTree()
        : m_root(nullptr){};

    binTree(TreeNode* node)
        : m_root(node){};
    [[maybe_unused]] explicit binTree(const string& str)
        : m_root(nullptr)
    {
        setBinTree(str);
    };
    ~binTree()
    {
        freeNode(m_root);
    };
    void freeBinTree()
    {
        freeNode(m_root);
        m_root = nullptr;
    }

    void setBinTree(const string& str)
    {
        vector intArray = extractIntArray(str);
        setBinTreeByInt(intArray);
    }

    [[nodiscard]] string flatBinTreeToStr() const
    {
        string flatStr = "[";
        vector<int> flatIntList = flattenBinTree();
        vector<string> flatStrList = convertStrList(flatIntList);
        if (flatStrList.empty())
            return "[]";
        for (auto&& str : flatStrList){
            flatStr += str;
            flatStr += ',';
        }
        flatStr[ flatStr.size() - 1 ] = ']';
        return flatStr;
    }

    [[maybe_unused]] void printTreeToScreen() const
    {
        vector<vector<string>> board;
        writeTreeToBoard(m_root, board);
        for (auto& i : board) {
            for (auto& j : i) {
                cout << '\t' << j;
            }
            cout << "\n\n";
        }
    }

    [[maybe_unused]] TreeNode* getTree()
    {
        return m_root;
    }
    explicit operator TreeNode*(){
        return this->m_root;
    }

};
template <class T>
concept fundamental = ::std::is_fundamental_v<std::remove_cvref_t<T>>;



template <class T>
concept Printable = requires{
    fundamental<T>;
};








class Printer{
    using utf8String=std::basic_string_view<char>;
    utf8String separatorChar;
    utf8String leftBraceChar;
    utf8String rightBraceChar;
public:
    constexpr Printer():separatorChar(","),leftBraceChar("["),rightBraceChar("]"){}
    [[nodiscard]] const utf8String& getSeparatorChar() const
    {
        return separatorChar;
    }
    void setSeparatorChar(const utf8String& separatorChar)
    {
        Printer::separatorChar = separatorChar;
    }
    [[nodiscard]] const utf8String& getLeftBraceChar() const
    {
        return leftBraceChar;
    }
    void setLeftBraceChar(const utf8String& leftBraceChar)
    {
        Printer::leftBraceChar = leftBraceChar;
    }
    [[nodiscard]] const utf8String& getRightBraceChar() const
    {
        return rightBraceChar;
    }
    void setRightBraceChar(const utf8String& rightBraceChar)
    {
        Printer::rightBraceChar = rightBraceChar;
    }
};

[[maybe_unused]] inline constexpr static Printer defaultPrinter;


template <class Range>
requires ::std::ranges::input_range<Range>
    std::string serilizeString(Range&& c,const Printer& printer)
{
    std::stringstream stream;
    stream << printer.getLeftBraceChar();
    for (auto&& e : c) {
        if constexpr (fundamental<::std::ranges::range_value_t<Range>>) {
            stream << e << printer.getSeparatorChar();
        }
        else {
            stream << serilizeString(e) << printer.getSeparatorChar() << '\n';
        }
    }
    stream << '\b' << printer.getRightBraceChar();
    return stream.str();
}



template <class Range>
requires ::std::ranges::input_range<Range>
    [[maybe_unused]] void print(Range&& r,const Printer& printer=defaultPrinter,std::ostream& os=std::cerr){
    using value_type = ::std::ranges::range_value_t<std::remove_cvref_t<Range>>;
    auto separatorChar=printer.getSeparatorChar();
    auto leftBraceChar=printer.getLeftBraceChar();
    auto rightBraceChar=printer.getRightBraceChar();
    if constexpr (fundamental<value_type>) {
        os << leftBraceChar;
    }
    else {
        os << leftBraceChar;
    }
    if constexpr (fundamental<value_type>) {
        for (auto&& e : r) {
            os << e << separatorChar;
        }

    } else {
        for (auto&& e : r) {
            os<<'\n'<<"    ";
            os << serilizeString(e,printer) << separatorChar << '\n';
        }
    }
    for(auto&&e:separatorChar){
        os << '\b';
    }
    os<< rightBraceChar<<'\n';
}
template <fundamental T>
[[maybe_unused]] void print(T t)
{
    std::cout<<t<<'\n';
}

[[maybe_unused]] void print(ListNode* root)
{
    printLinkedList(root);
}

[[maybe_unused]] void print(TreeNode* root)
{
    binTree tree(root);
    std::cout << tree.flatBinTreeToStr();
}

#endif  // LEETCODECPP_UTILITY_HPP
}