#pragma once
#include <concepts>
#include <iostream>
#include <queue>
#include <ranges>
#include <sstream>
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

class LinkedList {
    ListNode* head;
    bool free;

public:
    LinkedList(const std::initializer_list<int>& list)
    {
        auto begin = list.begin();
        auto end = list.end();
        if (list.size() == 0) {
            head = nullptr;
            return;
        }
        else {
            head = new ListNode(*begin++);
            ListNode* curNode = head;
            for (; begin != end; ++begin) {
                curNode->next = new ListNode(*begin);
                curNode = curNode->next;
            }
        }
    }
    [[maybe_unused]] explicit LinkedList(ListNode* raw)
        : head(raw)
        , free(false)
    {
    }

    [[nodiscard]] std::string to_string() const
    {
        std::stringstream ss;
        ListNode* curNode = head;
        while (curNode != nullptr) {
            ss << curNode->val<< " -> ";
            curNode = curNode->next;
        }
        ss << "null";
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

    ListNode* getHead()
    {
        auto head=this->head;
        this->head= nullptr;
        return head;
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

class [[maybe_unused]] BinaryTree {
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

    void writeRootToBoard(
        TreeNode* root, int height, int left, int right, ::std::vector<::std::vector<::std::string>>& board) const
    {
        if (root == nullptr)
            return;
        int mid = (left + right) / 2;
        board[ height ][ mid ] = ::std::to_string(root->val);
        writeRootToBoard(root->left, height + 1, left, mid - 1, board);
        writeRootToBoard(root->right, height + 1, mid + 1, right, board);
    }

    [[maybe_unused]] ::std::vector<::std::vector<::std::string>>
    writeTreeToBoard(TreeNode* root, ::std::vector<::std::vector<::std::string>>& board) const
    {
        int height = treeHeight(root);
        board = ::std::vector<::std::vector<::std::string>>(
            height, ::std::vector<::std::string>(std::pow(2, height) - 1, ""));
        writeRootToBoard(root, 0, 0, static_cast<int>(std::pow(2, height) - 2), board);
        return board;
    }

public:
    BinaryTree()
        : m_root(nullptr){};

    [[maybe_unused]] explicit BinaryTree(const ::std::string& str)
        : m_root(nullptr)
    {
        setBinTree(str);
    };
    ~BinaryTree()
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
        for (auto&& str : flatStrList) {
            flatStr += str;
            flatStr += ',';
        }
        flatStr[ flatStr.size() - 1 ] = ']';
        return flatStr;
    }

    [[maybe_unused]] [[nodiscard]] ::std::string to_string() const
    {
        return this->flatBinTreeToStr();
    }

    [[maybe_unused]] TreeNode* getTree()
    {
        return m_root;
    }
    explicit operator TreeNode*()
    {
        return this->m_root;
    }
};

template <class T>
concept StdToString = requires(T t)
{
    {
        std::to_string(t)
    }
    ->std::convertible_to<std::string>;
};

template <class T>
concept SelfToString = requires(T t)
{
    {
        std::declval<T>().to_string()
    }
    ->std::convertible_to<std::string>;
};

template <class T>
concept ToString = StdToString<T> || SelfToString<T> || std::convertible_to<std::string, std::remove_cvref_t<T>>;

template <class T>
concept Container = std::ranges::input_range<std::remove_cvref_t<T>>;

template <class T>
concept Printable = Container<T> || ToString<T>;

class Printer {
    using sepratorString = std::basic_string_view<char>;
    sepratorString separatorChar;
    sepratorString leftBraceChar;
    sepratorString rightBraceChar;

public:
    constexpr Printer()
        : separatorChar(",")
        , leftBraceChar("[")
        , rightBraceChar("]")
    {
    }
    [[nodiscard]] const sepratorString& getSeparatorChar() const
    {
        return separatorChar;
    }
    [[maybe_unused]] void setSeparatorChar(const sepratorString& ch)
    {
        Printer::separatorChar = ch;
    }
    [[nodiscard]] const sepratorString& getLeftBraceChar() const
    {
        return leftBraceChar;
    }
    [[maybe_unused]] void setLeftBraceChar(const sepratorString& ch)
    {
        Printer::leftBraceChar = ch;
    }
    [[nodiscard]] const sepratorString& getRightBraceChar() const
    {
        return rightBraceChar;
    }
    [[maybe_unused]] void setRightBraceChar(const sepratorString& ch)
    {
        Printer::rightBraceChar = ch;
    }
};

[[maybe_unused]] inline constexpr static Printer defaultPrinter;

template <ToString T>
inline ::std::string format_string(const T& t)
{
    using NoCvrT = std::remove_cvref_t<T>;
    if constexpr (std::convertible_to<std::string, NoCvrT>) {
        return std::string(t);
    }
    else if constexpr (SelfToString<T>) {
        return t.to_string();
    }
    else {
        return std::to_string(t);
    }
}

template <Container C>
requires ::std::ranges::input_range<C> [[maybe_unused]] inline ::std::string
format(C&& r, int deep, const Printer& printer = defaultPrinter)
{
    using value_type = ::std::ranges::range_value_t<std::remove_cvref_t<C>>;
    auto separatorChar = printer.getSeparatorChar();
    auto leftBraceChar = printer.getLeftBraceChar();
    auto rightBraceChar = printer.getRightBraceChar();
    ::std::stringstream os;
    if constexpr (std::convertible_to<value_type, std::string> || std::convertible_to<value_type, std::string_view>) {
        os << leftBraceChar;
        for (auto&& e : r) {
            os << '\"' << e << '\"' << separatorChar;
        }

        os << '\b' << rightBraceChar;
    }
    else if constexpr (Container<value_type>) {
        for (int i = 0; i < deep; ++i) {
            os << "    ";
        }
        os << leftBraceChar << '\n';
        for (auto&& e : r) {
            for (int i = 0; i < deep; ++i) {
                os << "    ";
            }
            os << format(e, deep + 1, printer) << separatorChar << '\n';
        }
        for (int i = 0; i < deep; ++i) {
            os << "    ";
        }
        os << rightBraceChar;
    }
    else if constexpr (ToString<value_type>) {
        for (int i = 0; i < deep; ++i) {
            os << "    ";
        }
        os << leftBraceChar;
        for (auto&& e : r) {
            os << format_string(e) << separatorChar;
        }
        os << '\b' << rightBraceChar;
    }
    return os.str();
}

template <Printable T>
inline void format_print(const T& object, std::ostream& os = std::cerr)
{
    if constexpr (ToString<T>) {
        os << format_string(object) << '\n';
    }
    else {
        os << format(object, 0) << '\n';
    }
}

template <Printable T>
[[maybe_unused]] inline void print(const T& t)
{
    format_print(t, std::cerr);
}

}  // namespace tools