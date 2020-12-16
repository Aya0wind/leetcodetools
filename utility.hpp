#pragma once
#include <cmath>
#include <concepts>
#include <iostream>
#include <queue>
#include <ranges>
#include <sstream>
#include <string>
#include <vector>
#include <type_traits>

namespace tools {

struct ListNode {
    int val;
    ListNode* next;
    explicit ListNode(int x)
        : val(x)
        , next(nullptr)
    {
    }
};

class LinkedList{
    ListNode* head;

public:
    LinkedList(const std::initializer_list<int>& list)
    {
        ::std::vector num(list);
        if (num.empty())
        {
            head= nullptr;
            return;
        }
        else {
            head = new ListNode(num[ 0 ]);
            ListNode* curNode = head;
            for (int i = 1; i < num.size(); i++) {
                curNode->next = new ListNode(num[ i ]);
                curNode = curNode->next;
            }
        }
    }

    [[nodiscard]] std::string to_string() const
    {
        std::stringstream ss;
        ListNode* curNode = head;
        while (curNode != nullptr) {
            ss << curNode->val << " -> ";
            curNode = curNode->next;
        }
        ss << "nullptr";
        return ss.str();
    }

    ~LinkedList()
    {
        ListNode* curNode = head;
        while (curNode != nullptr) {
            ListNode* delNode = curNode;
            curNode = curNode->next;
            delete delNode;
        }
    }
    ListNode* getRoot(){
        return this->head;
    }
};


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

    static ::std::vector<int> extractIntArray(::std::string str)
    {
        ::std::vector<int> intList;
        str = str.substr(1, str.size() - 2);
        str += ',';
        for (int pos = 0; pos < str.size(); pos += 1) {
            int tailPos = str.find(',', pos);
            ::std::string intStr = str.substr(pos, tailPos - pos);

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

    void setBinTreeByInt(::std::vector<int>& list)
    {
        ::std::queue<TreeNode*> q;
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

    [[nodiscard]] ::std::vector<int> flattenBinTree() const
    {
        ::std::vector<int> flatIntList;
        std::queue<TreeNode*> q;
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

    static ::std::vector<::std::string> convertStrList(::std::vector<int>& flatIntList)
    {
        ::std::vector<::std::string> flatStrList;
        for (auto var : flatIntList) {
            if (var == NULLPTR_VAR)
                flatStrList.emplace_back("null");
            else
                flatStrList.push_back(::std::to_string(var));
        }
        return flatStrList;
    }

    int treeHeight(TreeNode* root) const
    {
        if (root == nullptr)
            return 0;
        return std::max(treeHeight(root->left), treeHeight(root->right)) + 1;
    }

    void writeRootToBoard(TreeNode* root, int height, int left, int right, ::std::vector<::std::vector<::std::string>>& board) const
    {
        if (root == nullptr)
            return;
        int mid = (left + right) / 2;
        board[ height ][ mid ] = ::std::to_string(root->val);
        writeRootToBoard(root->left, height + 1, left, mid - 1, board);
        writeRootToBoard(root->right, height + 1, mid + 1, right, board);
    }

    [[maybe_unused]] ::std::vector<::std::vector<::std::string>> writeTreeToBoard(TreeNode* root, ::std::vector<::std::vector<::std::string>>& board) const
    {
        int height = treeHeight(root);
        board = ::std::vector<::std::vector<::std::string>>(height, ::std::vector<::std::string>(std::pow(2, height) - 1, ""));
        writeRootToBoard(root, 0, 0, static_cast<int>(std::pow(2, height) - 2), board);
        return board;
    }

public:
    binTree()
        : m_root(nullptr){};

    [[maybe_unused]] explicit binTree(const ::std::string& str)
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

    void setBinTree(const ::std::string& str)
    {
        ::std::vector intArray = extractIntArray(str);
        setBinTreeByInt(intArray);
    }

    [[nodiscard]] ::std::string flatBinTreeToStr() const
    {
        ::std::string flatStr = "[";
        ::std::vector<int> flatIntList = flattenBinTree();
        ::std::vector<::std::string> flatStrList = convertStrList(flatIntList);
        if (flatStrList.empty())
            return "[]";
        for (auto&& str : flatStrList){
            flatStr += str;
            flatStr += ',';
        }
        flatStr[ flatStr.size() - 1 ] = ']';
        return flatStr;
    }

    [[maybe_unused]] [[nodiscard]] ::std::string to_string() const{
        return this->flatBinTreeToStr();
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






template<class T>
concept ToString=requires{
    {std::declval<T>().to_string()}->std::convertible_to<std::string>;
};

template<class T>
concept Container=requires{
    std::ranges::input_range<T>&&std::convertible_to<T,::std::string>;
};

template <class T,class value=typename std::remove_cvref<T>::type>
concept Printable = requires{
    Container<value>||fundamental<value>||std::convertible_to<value,::std::string>||ToString<value>;
};




class Printer{
    using utf8string=std::basic_string_view<char>;
    utf8string separatorChar;
    utf8string leftBraceChar;
    utf8string rightBraceChar;
public:
    constexpr Printer():separatorChar(","),leftBraceChar("["),rightBraceChar("]"){}
    [[nodiscard]] const utf8string& getSeparatorChar() const
    {
        return separatorChar;
    }
    void setSeparatorChar(const utf8string& separatorChar)
    {
        Printer::separatorChar = separatorChar;
    }
    [[nodiscard]] const utf8string& getLeftBraceChar() const
    {
        return leftBraceChar;
    }
    void setLeftBraceChar(const utf8string& leftBraceChar)
    {
        Printer::leftBraceChar = leftBraceChar;
    }
    [[nodiscard]] const utf8string& getRightBraceChar() const
    {
        return rightBraceChar;
    }
    void setRightBraceChar(const utf8string& rightBraceChar)
    {
        Printer::rightBraceChar = rightBraceChar;
    }
};

[[maybe_unused]] inline constexpr static Printer defaultPrinter;


template <class Range>
requires ::std::ranges::input_range<Range>
    [[maybe_unused]] ::std::string format(Range&& r,int deep,const Printer& printer=defaultPrinter){
    using value_type = ::std::ranges::range_value_t<std::remove_cvref_t<Range>>;
    auto separatorChar=printer.getSeparatorChar();
    auto leftBraceChar=printer.getLeftBraceChar();
    auto rightBraceChar=printer.getRightBraceChar();
    ::std::stringstream os;
    if constexpr (fundamental<value_type>) {
        os<<leftBraceChar;
        for (auto&& e : r) {
            os << e << separatorChar;
        }
        os<<'\b'<<rightBraceChar;
    }else if constexpr (std::convertible_to<value_type,std::string>||std::convertible_to<value_type,std::string_view>){
        os<<leftBraceChar;
        for (auto&& e : r) {
            os <<'\"'<< e<<'\"'<< separatorChar;
        }
        os<<'\b'<<rightBraceChar;
    }
    else if constexpr (ToString<value_type>){
        os<<leftBraceChar;
        for (auto&& e : r) {
            os << e.to_string() << separatorChar;
        }
        os<<'\b'<<rightBraceChar;
    }else if constexpr (Container<value_type>) {
        os << leftBraceChar << '\n';
        for (auto&& e : r) {
            for (int i=0;i<deep;++i){
                os<< "    ";
            }
            os << format(e,deep+1,printer) << separatorChar << '\n';
        }
        os << rightBraceChar;
    }
    return os.str();
}

template <Printable T>
void format_print(const T& object,std::ostream& os=std::cerr){
    using value=typename std::remove_cvref<T>::type;
    constexpr bool is_std_printable=std::convertible_to<value,::std::string>||std::convertible_to<::std::string_view,value>;
    if constexpr (is_std_printable||fundamental<value>){
        os<<object<<'\n';
    }
    else if constexpr (ToString<value>){
        os<<object.to_string()<<'\n';
    }
    else{

    }
}

template <Printable T>
[[maybe_unused]] void print(const T& t)
{
    format_print(t,std::cerr);
}



}