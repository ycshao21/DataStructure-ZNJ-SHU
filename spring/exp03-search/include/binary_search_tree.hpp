#pragma once

#include <format>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

namespace myds
{

template <class K, class E>
struct BinarySearchTreeNode
{
    std::pair<K, E> data;  // { key, element }
    BinarySearchTreeNode<K, E>* leftChild = nullptr;
    BinarySearchTreeNode<K, E>* rightChild = nullptr;
};

template <class K, class E>
class BinarySearchTree
{
    using Node = BinarySearchTreeNode<K, E>;
    using Pair = std::pair<K, E>;

public:
    BinarySearchTree() : m_root(nullptr), m_size(0)
    {
    }
    BinarySearchTree(const BinarySearchTree<K, E>& tree)
        : m_root(_copyTree(tree.m_root)), m_size(tree.m_size)
    {
    }
    BinarySearchTree(const std::vector<Pair>& pairs);
    ~BinarySearchTree()
    {
        clear();
    }

    bool isEmpty() const
    {
        return m_size == 0;
    }
    int getSize() const
    {
        return m_size;
    }
    int getHeight() const
    {
        return _getHeight(m_root);
    }
    Pair* getRootElement() const
    {
        return m_root ? &m_root->data : nullptr;
    }

    Pair* find(const K& key) const;

    void clear();

    void insert(const K& key, const E& element);

    // Replace it with the maximum node in its left subtree.
    void erase_ver1(const K& key);
    // Replace it with the minimum node in its right subtree.
    void erase_ver2(const K& key);
    // Move its left subtree to the left subtree of the minimum node in its right
    // subtree.
    void erase_ver3(const K& key);
    // Move its right subtree to the right subtree of the maximum node in its left
    // subtree.
    void erase_ver4(const K& key);

    void preOrder(void (*visit)(Node*))
    {
        s_visit = visit;
        _preOrder(m_root);
    }
    void inOrder(void (*visit)(Node*))
    {
        s_visit = visit;
        _inOrder(m_root);
    }
    void postOrder(void (*visit)(Node*))
    {
        s_visit = visit;
        _postOrder(m_root);
    }

    void printElements() const
    {
        inOrder(printElement);
    }
    void printKeyTree(std::ostream& out = std::cout) const
    {
        _printKeyTree(m_root, out);
    }

private:
    Node* _copyTree(Node* r);
    static std::size_t _getHeight(Node* r);
    static void _preOrder(Node* r);
    static void _inOrder(Node* r);
    static void _inOrder(Node* r,
                         std::vector<Node*>& nodePtrVec);  // For outputTree function.
    static void _postOrder(Node* r);
    static void _printKeyTree(Node* r, std::ostream& out = std::cout);
    static void printElement(Node* r)
    {
        std::cout << r->data.second << " ";
    }
    static void dispose(Node* node)
    {
        delete node;
    }

    Node* m_root;
    std::size_t m_size;
    inline static void (*s_visit)(Node*) = nullptr;
};

template <class K, class E>
auto BinarySearchTree<K, E>::_getHeight(Node* root) -> std::size_t
{
    if (!root) {
        return 0;
    }
    return 1 + std::max(_getHeight(root->leftChild), _getHeight(root->rightChild));
}

template <class K, class E>
auto BinarySearchTree<K, E>::_copyTree(Node* root) -> Node*
{
    if (!root) {
        return nullptr;
    }
    Node* lChild = _copyTree(root->leftChild);
    Node* rChild = _copyTree(root->rightChild);
    return new Node{root->data, lChild, rChild};
}

template <class K, class E>
BinarySearchTree<K, E>::BinarySearchTree(const std::vector<Pair>& pairs)
{
    m_root = nullptr;
    m_size = 0;
    for (const auto& pair : pairs) {
        insert(pair.first, pair.second);
    }
}

template <class K, class E>
auto BinarySearchTree<K, E>::find(const K& key) const -> Pair*
{
    Node* cur = m_root;
    while (cur) {
        if (key < cur->data.first) {
            cur = cur->leftChild;
        } else if (key > cur->data.first) {
            cur = cur->rightChild;
        } else {
            return &cur->data;
        }
    }
    return nullptr;
}

template <class K, class E>
void BinarySearchTree<K, E>::clear()
{
    postOrder(dispose);
    m_root = nullptr;
    m_size = 0;
}

template <class K, class E>
void BinarySearchTree<K, E>::insert(const K& key, const E& element)
{
    Node* cur = m_root;
    Node* parent = nullptr;
    while (cur) {
        parent = cur;
        // Move cur to one of its child.
        if (key < cur->data.first) {
            cur = cur->leftChild;
        } else if (key > cur->data.first) {
            cur = cur->rightChild;
        } else {
            // If the key is already in the tree, cover the old value.
            cur->data.second = element;
            return;
        }
    }

    // Create a new node.
    cur = new Node{Pair{key, element}};
    if (m_root == nullptr) {
        m_root = cur;
    } else {
        if (key < parent->data.first) {
            parent->leftChild = cur;
        } else {
            parent->rightChild = cur;
        }
    }
    ++m_size;
}

template <class K, class E>
void BinarySearchTree<K, E>::erase_ver1(const K& key)
{
    Node* del = m_root;
    Node* delParent = nullptr;

    // Find the node to delete.
    while (del && del->data.first != key) {
        delParent = del;
        if (key < del->data.first) {
            del = del->leftChild;
        } else {
            del = del->rightChild;
        }
    }
    // The key is not in the tree.
    if (del == nullptr) {
        return;
    }

    // If del has no left child, replace it with its right child.
    if (del->leftChild == nullptr) {
        if (del == m_root) {
            m_root = del->rightChild;
        } else {
            if (delParent->leftChild == del) {
                delParent->leftChild = del->rightChild;
            } else {
                delParent->rightChild = del->rightChild;
            }
        }
        delete del;
    } else {  // Otherwise, replace it with the maximum node in its left subtree.
        Node* maxNode = del->leftChild;
        Node* maxParent = del;
        // Find the maximum node in the left subtree.
        while (maxNode->rightChild) {
            maxParent = maxNode;
            maxNode = maxNode->rightChild;
        }
        del->data = std::move(maxNode->data);
        if (maxParent->leftChild == maxNode) {
            maxParent->leftChild = maxNode->leftChild;
        } else {
            maxParent->rightChild = maxNode->leftChild;
        }
        delete maxNode;
    }
    m_size--;
}

template <class K, class E>
void BinarySearchTree<K, E>::erase_ver2(const K& key)
{
    Node* del = m_root;
    Node* delParent = nullptr;
    // Find the node to delete.
    while (del && del->data.first != key) {
        delParent = del;
        if (key < del->data.first) {
            del = del->leftChild;
        } else {
            del = del->rightChild;
        }
    }
    // The key is not in the tree.
    if (del == nullptr) {
        return;
    }

    // If del has no right child, replace it with its left child.
    if (del->rightChild == nullptr) {
        if (del == m_root) {
            m_root = del->leftChild;
        } else {
            if (delParent->leftChild == del) {
                delParent->leftChild = del->leftChild;
            } else {
                delParent->rightChild = del->leftChild;
            }
        }
        delete del;
    } else {  // Otherwise, replace it with the minimum node in its right subtree.
        Node* minNode = del->rightChild;
        Node* minParent = del;
        // Find the minimum node in the right subtree.
        while (minNode->leftChild) {
            minParent = minNode;
            minNode = minNode->leftChild;
        }
        del->data = std::move(minNode->data);

        if (minParent->rightChild == minNode) {
            minParent->rightChild = minNode->rightChild;
        } else {
            minParent->leftChild = minNode->rightChild;
        }
        delete minNode;
    }
    m_size--;
}

template <class K, class E>
void BinarySearchTree<K, E>::erase_ver3(const K& key)
{
    Node* del = m_root;
    Node* delParent = nullptr;
    // Find the node to delete.
    while (del && del->data.first != key) {
        delParent = del;
        if (key < del->data.first) {
            del = del->leftChild;
        } else {
            del = del->rightChild;
        }
    }
    // The key is not in the tree.
    if (del == nullptr) {
        return;
    }

    // If del has no right child, replace it with its left child.
    if (del->rightChild == nullptr) {
        if (del == m_root) {
            m_root = del->leftChild;
        } else {
            if (delParent->leftChild == del) {
                delParent->leftChild = del->leftChild;
            } else {
                delParent->rightChild = del->leftChild;
            }
        }
        delete del;
        m_size--;
        return;
    }
    // If del has left subtree, move it to the left subtree of the minimum node in
    // del's right subtree.
    if (del->leftChild) {
        Node* minNode = del->rightChild;
        // Find the minimum node in the right subtree.
        while (minNode->leftChild) {
            minNode = minNode->leftChild;
        }
        minNode->leftChild = del->leftChild;
    }
    if (del == m_root) {
        m_root = del->rightChild;
    } else {
        if (delParent->leftChild == del) {
            delParent->leftChild = del->rightChild;
        } else {
            delParent->rightChild = del->rightChild;
        }
    }
    delete del;
    m_size--;
}

template <class K, class E>
void BinarySearchTree<K, E>::erase_ver4(const K& key)
{
    Node* del = m_root;
    Node* delParent = nullptr;
    // Find the node to delete.
    while (del && del->data.first != key) {
        delParent = del;
        del = key < del->data.first ? del->leftChild : del->rightChild;
    }
    // The key is not in the tree.
    if (!del) {
        return;
    }

    // If del has no left child, replace it with its right child.
    if (!del->leftChild) {
        if (del == m_root) {
            m_root = del->rightChild;
        } else {
            if (delParent->leftChild == del) {
                delParent->leftChild = del->rightChild;
            } else {
                delParent->rightChild = del->rightChild;
            }
        }
        delete del;
        m_size--;
        return;
    }
    // If del has right subtree, move it to the right subtree of the maximum node
    // in del's left subtree.
    if (del->rightChild) {
        Node* maxNode = del->leftChild;
        // Find the minimum node in the right subtree.
        while (maxNode->rightChild) {
            maxNode = maxNode->rightChild;
        }
        maxNode->rightChild = del->rightChild;
    }
    if (del == m_root) {
        m_root = del->leftChild;
    } else {
        if (delParent->leftChild == del) {
            delParent->leftChild = del->leftChild;
        } else {
            delParent->rightChild = del->leftChild;
        }
    }
    delete del;
    m_size--;
}

template <class K, class E>
void BinarySearchTree<K, E>::_preOrder(Node* r)
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

template <class K, class E>
void BinarySearchTree<K, E>::_inOrder(Node* r)
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

template <class K, class E>
void BinarySearchTree<K, E>::_inOrder(Node* r, std::vector<Node*>& nodePtrVec)
{
    if (r == nullptr) {
        return;
    }

    _inOrder(r->leftChild, nodePtrVec);
    nodePtrVec.push_back(r);
    _inOrder(r->rightChild, nodePtrVec);
}

template <class K, class E>
void BinarySearchTree<K, E>::_postOrder(Node* r)
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

template <class K, class E>
void BinarySearchTree<K, E>::_printKeyTree(Node* r, std::ostream& out)
{
    if (r == nullptr) {
        return;
    }

    // Get the width of the tree.
    std::vector<Node*> ptrs;
    _inOrder(r, ptrs);

    std::size_t totalWidth = 0;
    std::unordered_map<Node*, std::size_t> beginPositions;  // Position of each node.
    for (const auto& p : ptrs) {
        beginPositions[p] = totalWidth;
        std::string nodeStr = std::format("{} ", p->data.first);
        totalWidth += nodeStr.size();
    }

    // Level-order traversal to print the tree.
    std::queue<Node*> q;
    q.push(r);

    while (!q.empty()) {
        std::string firstLine(totalWidth, ' ');
        std::string secondLine(totalWidth, ' ');

        // Traverse the current level.
        std::size_t numNodesOnCurLevel = q.size();

        for (std::size_t i = 0; i < numNodesOnCurLevel; ++i) {
            Node* curNode = q.front();
            q.pop();

            std::size_t nodePos = beginPositions[curNode];

            // If the node has a left child, connect them with '\' on the second line
            // and '_'s on the first line.
            if (curNode->leftChild) {
                q.push(curNode->leftChild);

                std::size_t slashPos = beginPositions[curNode->leftChild] + 1;
                secondLine[slashPos] = '/';

                std::fill(firstLine.begin() + slashPos + 1, firstLine.begin() + nodePos, '_');
            }

            // Print the element on the first line.
            std::string nodeStr = std::format("{}", curNode->data.first);
            for (std::size_t j = 0; j < nodeStr.size(); ++j) {
                firstLine[nodePos + j] = nodeStr[j];
            }

            // If the node has a right child, connect them with '\' on the second line
            // and '_'s on the first line.
            if (curNode->rightChild) {
                q.push(curNode->rightChild);

                std::size_t backSlashPos = beginPositions[curNode->rightChild] - 1;
                secondLine[backSlashPos] = '\\';

                std::fill(firstLine.begin() + nodePos + nodeStr.size(),
                          firstLine.begin() + backSlashPos, '_');
            }
        }

        // Print the current level.
        out << firstLine << '\n';
        out << secondLine << '\n';
    }
}
}  // namespace myds
