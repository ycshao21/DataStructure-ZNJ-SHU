#pragma once

#include <format>
#include <iostream>
#include <print>
#include <queue>
#include <ranges>
#include <unordered_map>

namespace myds
{

template <class T>
struct BinaryTreeNode
{
    T data;
    BinaryTreeNode<T>* leftChild = nullptr;
    BinaryTreeNode<T>* rightChild = nullptr;
};

template <class T>
class BinaryTree
{
    using VisitFn = void (*)(BinaryTreeNode<T>*);

public:
    // @brief Construct an empty binary tree.
    BinaryTree() = default;
    /**
     * @brief Construct a binary tree from a data and two subtrees.
     * @param data The data of the root.
     * @param left The left subtree.
     * @param right The right subtree.
     */
    BinaryTree(const T& data, const BinaryTree& left, const BinaryTree& right)
    {
        makeTree(data, left, right);
    }
    /**
     * @brief Copy constructor.
     * @param tree Another tree to be copied.
     */
    BinaryTree(const BinaryTree<T>& tree);
    /**
     * @brief Copy assignment.
     * @param tree Another tree to be copied.
     */
    BinaryTree<T>& operator=(const BinaryTree<T>& tree);
    // @brief Destructor.
    ~BinaryTree()
    {
        clear();
    }

    // @brief Return if the tree is empty.
    bool isEmpty() const
    {
        return m_size == 0;
    }
    // @brief Get the number of elements in the tree.
    int getSize() const
    {
        return m_size;
    }
    // @brief Get the height of the tree.
    int getHeight() const
    {
        return _getHeight(m_root);
    }
    // @brief Get the pointer to the root element.
    T* getRootElement() const
    {
        return m_root ? &m_root->data : nullptr;
    }

    /**
     * @brief Combine two subtrees and an element to make a new tree.
     * @param element Parent of the two subtrees.
     * @param left Left subtree.
     * @param right Right subtree.
     */
    void makeTree(const T& element, const BinaryTree<T>& left,
                  const BinaryTree<T>& right);
    // @brief Swap all the left and right children in the tree.
    void revolute()
    {
        _revolute(m_root);
    }
    // @brief Remove all the elements in the tree.
    void clear();

    /**
     * @brief Traverse the tree in preorder.
     * @param visit A function to be called on each node.
     */
    void preOrder(VisitFn visit)
    {
        s_visit = visit;
        _preOrder(m_root);
    }
    /**
     * @brief Traverse the tree in inorder.
     * @param visit A function to be called on each node.
     */
    void inOrder(VisitFn visit)
    {
        s_visit = visit;
        _inOrder(m_root);
    }
    /**
     * @brief Traverse the tree in postorder.
     * @param visit A function to be called on each node.
     */
    void postOrder(VisitFn visit)
    {
        s_visit = visit;
        _postOrder(m_root);
    }
    /**
     * @brief Traverse the tree in levelorder.
     * @param visit A function to be called on each node.
     */
    void levelOrder(VisitFn visit)
    {
        s_visit = visit;
        _levelOrder(m_root);
    }
    /**
     * @brief Print the tree to the output stream.
     * @param out Output stream.
     */
    void print(std::ostream& out = std::cout) const
    {
        _print(m_root, out);
    }

private:
    /**
     * @brief Copy all the nodes in a tree.
     * @param r Root of the tree.
     */
    static BinaryTreeNode<T>* copyTree(BinaryTreeNode<T>* r);
    /**
     * @brief Remove the node.
     * @param node The node to be removed.
     */
    static void dispose(BinaryTreeNode<T>* node)
    {
        delete node;
    }

    /**
     * @brief Get the height of a binary tree.
     * @param r Root of the tree.
     */
    static int _getHeight(BinaryTreeNode<T>* r);
    /**
     * @brief Swap all the left and right children in a tree.
     * @param r Root of the tree.
     */
    static void _revolute(BinaryTreeNode<T>* r);

    /**
     * @brief Traverse the tree in preorder.
     * @param r Root of the tree.
     */
    static void _preOrder(BinaryTreeNode<T>* r);
    /**
     * @brief Traverse the tree in inorder.
     * @param r Root of the tree.
     */
    static void _inOrder(BinaryTreeNode<T>* r);
    /**
     * @brief Traverse the tree and get the inorder sequence (for output
     * function).
     * @param r Root of the tree.
     */
    static void _inOrder(BinaryTreeNode<T>* r,
                         std::vector<BinaryTreeNode<T>*>& nodePtrVec);
    /**
     * @brief Traverse the tree in postorder.
     * @param r Root of the tree.
     */
    static void _postOrder(BinaryTreeNode<T>* r);
    /**
     * @brief Traverse the tree in levelorder.
     * @param r Root of the tree.
     */
    static void _levelOrder(BinaryTreeNode<T>* r);
    /**
     * @brief Print the tree vertically.
     * @param r Root of the tree.
     * @param out Output stream.
     */
    static void _print(BinaryTreeNode<T>* r, std::ostream& out);

    BinaryTreeNode<T>* m_root = nullptr;      // Pointer to the root.
    std::size_t m_size = 0;                   // Number of elements.
    inline static VisitFn s_visit = nullptr;  // Function to be called on each node.
};

////////////////////////////////////////////////////////////////////////////////////////////////
// Implementation of public member functions.
////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
BinaryTree<T>::BinaryTree(const BinaryTree<T>& tree)
    : m_root(copyTree(tree.m_root)), m_size(tree.m_size)
{
}

template <class T>
BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree<T>& tree)
{
    if (this != &tree) {
        m_root = copyTree(tree.m_root);
        m_size = tree.m_size;
    }
    return *this;
}

template <class T>
void BinaryTree<T>::makeTree(const T& element, const BinaryTree<T>& left,
                             const BinaryTree<T>& right)
{
    clear();
    m_root = new BinaryTreeNode<T>{element, copyTree(left.m_root), copyTree(right.m_root)};
    m_size = left.m_size + right.m_size + 1;
}

template <class T>
void BinaryTree<T>::clear()
{
    postOrder(dispose);
    m_root = nullptr;
    m_size = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////
// Implementation of private member functions.
////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
BinaryTreeNode<T>* BinaryTree<T>::copyTree(BinaryTreeNode<T>* r)
{
    if (r == nullptr) {
        return nullptr;
    }
    return new BinaryTreeNode<T>{r->data, copyTree(r->leftChild),
                                 copyTree(r->rightChild)};
}

template <class T>
int BinaryTree<T>::_getHeight(BinaryTreeNode<T>* r)
{
    if (r == nullptr) {
        return 0;
    }
    return 1 + std::max(_getHeight(r->leftChild), _getHeight(r->rightChild));
}

template <class T>
void BinaryTree<T>::_revolute(BinaryTreeNode<T>* r)
{
    if (r == nullptr) {
        return;
    }

    // Swap the left and right children.
    std::swap(r->leftChild, r->rightChild);

    // Revolute the left and right subtrees.
    _revolute(r->leftChild);
    _revolute(r->rightChild);
}

template <class T>
void BinaryTree<T>::_preOrder(BinaryTreeNode<T>* r)
{
    if (r == nullptr) {
        return;
    }

    if (s_visit) {
        s_visit(r);
    }
    _preOrder(r->leftChild);
    _preOrder(r->rightChild);
}

template <class T>
void BinaryTree<T>::_inOrder(BinaryTreeNode<T>* r)
{
    if (r == nullptr) {
        return;
    }

    _inOrder(r->leftChild);
    if (s_visit) {
        s_visit(r);
    }
    _inOrder(r->rightChild);
}

template <class T>
void BinaryTree<T>::_inOrder(BinaryTreeNode<T>* r,
                             std::vector<BinaryTreeNode<T>*>& nodePtrVec)
{
    if (r == nullptr) {
        return;
    }

    _inOrder(r->leftChild, nodePtrVec);
    nodePtrVec.push_back(r);
    _inOrder(r->rightChild, nodePtrVec);
}

template <class T>
void BinaryTree<T>::_postOrder(BinaryTreeNode<T>* r)
{
    if (r == nullptr) {
        return;
    }

    _postOrder(r->leftChild);
    _postOrder(r->rightChild);
    if (s_visit) {
        s_visit(r);
    }
}

template <class T>
void BinaryTree<T>::_levelOrder(BinaryTreeNode<T>* r)
{
    if (r == nullptr) {
        return;
    }

    std::queue<BinaryTreeNode<T>*> q;
    q.push(r);

    while (!q.empty()) {
        BinaryTreeNode<T>* cur = q.front();
        q.pop();

        if (s_visit) {
            s_visit(cur);
        }

        if (cur->leftChild) {
            q.push(cur->leftChild);
        }
        if (cur->rightChild) {
            q.push(cur->rightChild);
        }
    }
}

template <class T>
void BinaryTree<T>::_print(BinaryTreeNode<T>* r, std::ostream& out)
{
    if (r == nullptr) {
        return;
    }

    // Get the width of the tree.
    std::vector<BinaryTreeNode<T>*> nodes;
    _inOrder(r, nodes);

    std::string widthStr;
    std::unordered_map<BinaryTreeNode<T>*, int> pos;  // Position of each node.
    for (auto& p : nodes) {
        pos[p] = (int) widthStr.size();           // Record the position of the node.
        widthStr += std::format("{} ", p->data);  // Convert the element to string
                                                  // and append it to the result.
    }
    int width = (int) widthStr.size();

    // Levelorder traversal to print the tree.
    std::queue<BinaryTreeNode<T>*> q;
    q.push(r);
    while (!q.empty()) {
        std::string firstLine(width, ' '), secondLine(width, ' ');
        // Traverse the current level.
        int curLevelSize = (int) q.size();
        for (int i = 0; i < curLevelSize; ++i) {
            BinaryTreeNode<T>* curNodePtr = q.front();
            q.pop();
            int elemPos = pos[curNodePtr];
            // If the node has a left child, connect them with '\' on the second line
            // and '_'s on the first line.
            if (curNodePtr->leftChild) {
                q.push(curNodePtr->leftChild);
                int slashPos = pos[curNodePtr->leftChild] + 1;
                secondLine[slashPos] = '/';
                for (int j = slashPos + 1; j < elemPos; ++j) {
                    firstLine[j] = '_';
                }
            }
            // Print the element on the first line.
            std::string elemStr = std::format("{}", curNodePtr->data);
            for (std::size_t j = 0; j < elemStr.size(); ++j, ++elemPos) {
                firstLine[elemPos] = elemStr[j];
            }

            // If the node has a right child, connect them with '\' on the second line
            // and '_'s on the first line.
            if (curNodePtr->rightChild) {
                q.push(curNodePtr->rightChild);
                int backSlashPos = pos[curNodePtr->rightChild] - 1;
                secondLine[backSlashPos] = '\\';
                for (int j = backSlashPos - 1; j > elemPos; --j) {
                    firstLine[j] = '_';
                }
            }
        }
        // Print the current level.
        std::println(out, "{}", firstLine);
        std::println(out, "{}", secondLine);
    }
}

// @brief Output the tree to the output stream.
template <class T>
std::ostream& operator<<(std::ostream& out, const BinaryTree<T>& tree)
{
    tree.print(out);
    return out;
}

}  // namespace myds
